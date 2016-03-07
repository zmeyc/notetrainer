// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QSplitter>
#include <QLabel>
#include <QDesktopWidget>
#include <QMessageBox>
#include "MainWindow.h"
#include "Controls/NoteSelector.h"
#include "Controls/NoteGuess.h"
#include "Controllers/MidiReader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QSplitter *splitter = new QSplitter;
    splitter->setContentsMargins(10, 10, 10, 10);

    noteSelector_ = new NoteSelector;
    noteGuess_ = new NoteGuess;
    connect(noteGuess_, SIGNAL(reset()),
            this, SLOT(onReset()));

    splitter->addWidget(noteSelector_);
    splitter->addWidget(noteGuess_);

    setCentralWidget(splitter);

    MidiReader *reader = MidiReader::sharedInstance();
    if (!reader->init()) {
        QMessageBox::critical(this, tr("NoteTrainer"),
                              tr("Unable to initialize MIDI reader: ") +
                              reader->lastErrorMessage());
    }
    if (!reader->openPort(0)) {
        QMessageBox::critical(this, tr("NoteTrainer"),
                              tr("Unable to open MIDI port: ") +
                              reader->lastErrorMessage());
    }

    onReset();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onReset()
{
    QSet<Note> notes = noteSelector_->notes();
    noteGuess_->setNotes(notes);
    noteGuess_->start();
}
