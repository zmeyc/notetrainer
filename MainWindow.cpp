// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QSplitter>
#include <QLabel>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "Controls/StaffSettings.h"
#include "Controls/NoteSelector.h"
#include "Controls/NoteGuess.h"
#include "Controllers/MidiReader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    staffSettings_ = new StaffSettings;

    QSplitter *splitter = new QSplitter;
    splitter->setContentsMargins(10, 10, 10, 10);

    noteSelector_ = new NoteSelector;
    noteGuess_ = new NoteGuess;
    connect(noteGuess_, SIGNAL(reset()),
            this, SLOT(onReset()));

    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->addWidget(staffSettings_);
    leftPanelLayout->addWidget(noteSelector_);
    leftPanelLayout->addStretch(1);
    QWidget *leftPanel = new QWidget;
    leftPanel->setLayout(leftPanelLayout);

    splitter->addWidget(leftPanel);
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
    noteGuess_->setOctaveFrom(noteSelector_->octaveFrom());
    noteGuess_->setOctaveTo(noteSelector_->octaveTo());
    noteGuess_->setQueueLength(staffSettings_->queueLength());
    noteGuess_->setShowNoteNames(staffSettings_->showNoteNames());
    noteGuess_->setNotes(notes);
    noteGuess_->start();
}
