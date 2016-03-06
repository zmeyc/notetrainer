// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QSplitter>
#include <QLabel>
#include <QDesktopWidget>
#include "MainWindow.h"
#include "Controls/NoteSelector.h"
#include "Controls/NoteGuess.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QSplitter *splitter = new QSplitter;
    splitter->setContentsMargins(10, 10, 10, 10);

    NoteSelector *noteSelector = new NoteSelector;
    NoteGuess *noteGuess = new NoteGuess;

    splitter->addWidget(noteSelector);
    splitter->addWidget(noteGuess);

    setCentralWidget(splitter);
}

MainWindow::~MainWindow()
{
}
