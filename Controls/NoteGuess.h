// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTEGUESS_H
#define NOTEGUESS_H

#include <QWidget>
#include <QSet>
#include "Data/Note.h"

class QLineEdit;
class NoteView;
class StaffGraphicsItem;

class NoteGuess : public QWidget
{
    Q_OBJECT
public:
    explicit NoteGuess(QWidget *parent = 0);

    QSet<Note> notes() const;
    void setNotes(const QSet<Note> &notes);

    void start();

signals:
    void reset();

public slots:

protected slots:
    void onNoteOn(int key, int velocity);
    void onNoteOff(int key, int velocity);

protected:
    void initNoteView();
    void randomizeNextNote(bool allowRepeats);
    void correctNotePressed();
    void wrongNotePressed();

    QLineEdit *correctLineEdit_ = nullptr;
    QLineEdit *wrongLineEdit_ = nullptr;
    NoteView *noteView_ = nullptr;
    StaffGraphicsItem *staff_ = nullptr;
    QSet<Note> notes_;

    bool started_ = false;
    Note noteToGuess_;
};

#endif // NOTEGUESS_H
