// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTEGUESS_H
#define NOTEGUESS_H

#include <QWidget>

class NoteView;
class StaffGraphicsItem;

class NoteGuess : public QWidget
{
    Q_OBJECT
public:
    explicit NoteGuess(QWidget *parent = 0);

signals:

public slots:

protected slots:
    void onNoteOn(int key, int velocity);
    void onNoteOff(int key, int velocity);

protected:
    void initNoteView();

    NoteView *noteView_ = nullptr;
    StaffGraphicsItem *staff_ = nullptr;
};

#endif // NOTEGUESS_H
