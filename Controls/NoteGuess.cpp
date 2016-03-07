// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "NoteGuess.h"
#include "Controls/NoteView.h"
#include "GraphicsItems/StaffGraphicsItem.h"
#include "Controllers/MidiReader.h"

NoteGuess::NoteGuess(QWidget *parent) : QWidget(parent)
{
    QLabel *correct = new QLabel("Correct");
    QLabel *wrong = new QLabel("Wrong");
    QPushButton *reset = new QPushButton("Reset");

    QHBoxLayout *panelLayout = new QHBoxLayout;
    panelLayout->addWidget(correct);
    panelLayout->addWidget(wrong);
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

void NoteGuess::onNoteOn(int key, int velocity)
{
    Q_UNUSED(velocity);
    Note note = noteFromKey(key);
    staff_->addNote(note, 0);
}

void NoteGuess::onNoteOff(int key, int velocity)
{
    Q_UNUSED(velocity);
    Note note = noteFromKey(key);
    staff_->removeNote(note, 0);
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
