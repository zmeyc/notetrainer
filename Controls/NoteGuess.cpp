// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
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

    QTimer::singleShot(0, this, SLOT(initNoteView()));
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
    if (octaveFrom_ != octaveFrom)
        update();
    octaveFrom_ = octaveFrom;
}

int NoteGuess::octaveTo() const
{
    return octaveTo_;
}

void NoteGuess::setOctaveTo(int octaveTo)
{
    if (octaveTo_ != octaveTo)
        update();
    octaveTo_ = octaveTo;
}

void NoteGuess::onNoteOn(int key, int velocity)
{
    Q_UNUSED(velocity);
    Note note = Note::noteFromKey(key);
    staff_->addNote(note);
}

void NoteGuess::onNoteOff(int key, int velocity)
{
    Q_UNUSED(velocity);
    Note note = Note::noteFromKey(key);
    staff_->removeNote(note);

    if (started_) {
        if (noteToGuess_ == note) {
            correctNotePressed();
            randomizeNextNote(false);
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

void NoteGuess::randomizeNextNote(bool allowRepeats)
{
    staff_->removeAllNotes();

    QSet<Note> t = notes_;
    if (!allowRepeats)
        t.remove(noteToGuess_);

    if (t.isEmpty())
        return;

    Note note = t.toList().at(qrand() % t.size());

    staff_->addNote(note);
    noteToGuess_ = note;
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
    randomizeNextNote(true);
    started_ = true;
}
