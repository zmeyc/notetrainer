// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTE_H
#define NOTE_H

#include <QString>

class Note {
public:
    enum class Pitch {
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

    Note(Pitch pitch = Pitch::C, int octave = 4);

    static Note noteFromKey(int key);

    static QString pitchName(Pitch pitch);
    QString pitchName() const;
    bool isFilled() const;

    Pitch pitch() const;
    void setPitch(const Pitch &pitch);

    int octave() const;
    void setOctave(int octave);

    bool operator== (const Note &other) const;
    bool operator< (const Note &other) const;

protected:
    Pitch pitch_ = Pitch::C;
    int octave_ = 4;
};

uint qHash(Note note);

#endif // NOTE_H
