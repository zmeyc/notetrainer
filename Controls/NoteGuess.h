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

    int octaveFrom() const;
    void setOctaveFrom(int octaveFrom);

    int octaveTo() const;
    void setOctaveTo(int octaveTo);

    int queueLength() const;
    void setQueueLength(int queueLength);

    void start();

signals:
    void reset();

public slots:

protected slots:
    void onNoteOn(int key, int velocity);
    void onNoteOff(int key, int velocity);

protected:
    enum {
        GroupMain,
        GroupUserInput
    };

    Q_SLOT void initNoteView();
    void fillQueueWithNotes();
    bool randomizeNextNote();
    void correctNotePressed();
    void wrongNotePressed();

    QLineEdit *correctLineEdit_ = nullptr;
    QLineEdit *wrongLineEdit_ = nullptr;
    NoteView *noteView_ = nullptr;
    StaffGraphicsItem *staff_ = nullptr;
    QSet<Note> notes_;
    int octaveFrom_ = 0;
    int octaveTo_ = 0;
    int queueLength_ = 0;

    bool started_ = false;

    bool hasLastGeneratedNote_ = false;
    Note lastGeneratedNote_;
};

#endif // NOTEGUESS_H
