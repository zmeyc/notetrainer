// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "NoteGuess.h"
#include "Controls/NoteView.h"
#include "GraphicsItems/StaffGraphicsItem.h"
#include "Controllers/MidiReader.h"
#include "Utils/Utils.h"

NoteGuess::NoteGuess(QWidget *parent) : QWidget(parent)
{
    QLabel *correctLabel = new QLabel(tr("Correct"));
    correctLineEdit_ = new QLineEdit();
    correctLineEdit_->setReadOnly(true);
    QLabel *wrongLabel = new QLabel(tr("Wrong"));
    wrongLineEdit_ = new QLineEdit();
    wrongLineEdit_->setReadOnly(true);
    QPushButton *reset = new QPushButton(tr("Reset"));
    connect(reset, SIGNAL(clicked(bool)),
            this, SIGNAL(reset()));

    QHBoxLayout *panelLayout = new QHBoxLayout;
    panelLayout->addWidget(correctLabel);
    panelLayout->addWidget(correctLineEdit_);
    panelLayout->addWidget(wrongLabel);
    panelLayout->addWidget(wrongLineEdit_);
    panelLayout->addStretch(1);
    panelLayout->addWidget(reset);

    noteView_ = new NoteView;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(noteView_);
    layout->addLayout(panelLayout);

    setLayout(layout);

    initNoteView();
}

QSet<Note> NoteGuess::notes() const
{
    return notes_;
}

void NoteGuess::setNotes(const QSet<Note> &notes)
{
    notes_ = notes;
//    if (notes.empty()) {
//        fromOctave_ = toOctave_ = 4;
//        return;
//    } else {
//        fromOctave_ = INT_MAX;
//        toOctave_ = INT_MIN;
//        foreach (const Note &note, notes) {
//            if (note.octave() < fromOctave_)
//                fromOctave_ = note.octave();
//            if (note.octave() > toOctave_)
//                toOctave_ = note.octave();
//        }
//    }
}

int NoteGuess::octaveFrom() const
{
    return octaveFrom_;
}

void NoteGuess::setOctaveFrom(int octaveFrom)
{
    octaveFrom_ = octaveFrom;
}

int NoteGuess::octaveTo() const
{
    return octaveTo_;
}

void NoteGuess::setOctaveTo(int octaveTo)
{
    octaveTo_ = octaveTo;
}

int NoteGuess::queueLength() const
{
    return queueLength_;
}

void NoteGuess::setQueueLength(int queueLength)
{
    queueLength_ = queueLength;
}

void NoteGuess::onNoteOn(int key, int velocity)
{
    Q_UNUSED(velocity);
    Note note = Note::noteFromKey(key);
    staff_->addNote(0, note, GroupUserInput);
}

void NoteGuess::onNoteOff(int key, int velocity)
{
    Q_UNUSED(velocity);
    Note note = Note::noteFromKey(key);
    staff_->removeNote(0, note, GroupUserInput);

    if (started_) {
        if (staff_->hasNote(0, note, GroupMain)) {
            staff_->queuePop();
            correctNotePressed();
            fillQueueWithNotes();
        } else {
            wrongNotePressed();
        }
    }
}

void NoteGuess::initNoteView()
{
    MidiReader *reader = MidiReader::sharedInstance();

    staff_ = new StaffGraphicsItem;
    connect(reader, SIGNAL(noteOn(int,int)),
            this, SLOT(onNoteOn(int,int)));
    connect(reader, SIGNAL(noteOff(int,int)),
            this, SLOT(onNoteOff(int,int)));

    noteView_->scene()->addItem(staff_);

//    staff->addNote(Note::C, 0);
//    staff->removeAllNotes();
    //    staff->addNote(Note::F, 0);
}

void NoteGuess::fillQueueWithNotes()
{
    while (staff_->queueLength() < queueLength_) {
        if (!randomizeNextNote())
            return;
    }
}

bool NoteGuess::randomizeNextNote()
{
    QSet<Note> t = notes_;
    if (t.size() > 1 && hasLastGeneratedNote_)
        t.remove(lastGeneratedNote_);

    if (t.isEmpty())
        return false;

    Note note = t.toList().at(qrand() % t.size());

    staff_->queuePushNote(note, GroupMain);
    lastGeneratedNote_ = note;
    hasLastGeneratedNote_ = true;
    return true;
}

void NoteGuess::correctNotePressed()
{
    int correct = correctLineEdit_->text().toInt();
    ++correct;
    correctLineEdit_->setText(QString::number(correct));
}

void NoteGuess::wrongNotePressed()
{
    int wrong = wrongLineEdit_->text().toInt();
    ++wrong;
    wrongLineEdit_->setText(QString::number(wrong));
}

void NoteGuess::start()
{
    correctLineEdit_->setText("0");
    wrongLineEdit_->setText("0");
    staff_->setOctaveRange(octaveFrom_, octaveTo_);
    hasLastGeneratedNote_ = false;
    staff_->removeAllNotes();
    fillQueueWithNotes();
    started_ = true;
}
