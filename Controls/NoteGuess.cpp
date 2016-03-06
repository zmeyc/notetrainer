// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "NoteGuess.h"
#include "Controls/NoteView.h"
#include "GraphicsItems/StaffGraphicsItem.h"

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

void NoteGuess::initNoteView()
{
    StaffGraphicsItem *staff = new StaffGraphicsItem;
    noteView_->scene()->addItem(staff);

    staff->addNote(Note::C, 0);
    staff->addNote(Note::F, 0);
}
