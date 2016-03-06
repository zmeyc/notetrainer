// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QSplitter>
#include <QLabel>
#include "MainWindow.h"
#include "Controls/NoteSelector.h"
#include "Utils/WidgetUtils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setGeometry(geometry().x(), geometry().y(), 800, 600);

    QSplitter *splitter = new QSplitter;

    NoteSelector *noteSelector = new NoteSelector;
    QLabel *play = new QLabel("Play");
    WidgetUtils::setBackgroundColor(play, Qt::green);

    splitter->addWidget(noteSelector);
    splitter->addWidget(play);

    setCentralWidget(splitter);
}

MainWindow::~MainWindow()
{
}
