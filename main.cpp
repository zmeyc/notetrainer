// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(time(0));

    MainWindow w;
    w.show();

    return a.exec();
}
