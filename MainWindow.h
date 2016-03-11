// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StaffSettings;
class NoteSelector;
class NoteGuess;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void onReset();

protected:
    StaffSettings *staffSettings_ = nullptr;
    NoteSelector *noteSelector_ = nullptr;
    NoteGuess *noteGuess_ = nullptr;
};

#endif // MAINWINDOW_H
