// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTEGUESS_H
#define NOTEGUESS_H

#include <QWidget>

class NoteView;

class NoteGuess : public QWidget
{
    Q_OBJECT
public:
    explicit NoteGuess(QWidget *parent = 0);

signals:

public slots:

protected:
    void initNoteView();

    NoteView *noteView_ = nullptr;
};

#endif // NOTEGUESS_H
