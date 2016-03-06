// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTE_H
#define NOTE_H

#include <QString>

enum class Note {
    C = 0,
    Cis,
    D,
    Ees,
    E,
    F,
    Fis,
    G,
    Aes,
    A,
    Bes,
    B,

    Count
};

QString noteName(Note note);

#endif // NOTE_H
