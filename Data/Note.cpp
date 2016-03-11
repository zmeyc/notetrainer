// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QHashFunctions>
#include "Note.h"
#include "Utils/Utils.h"

Note::Note(Note::Pitch pitch, int octave)
    : pitch_(pitch)
    , octave_(octave)
{

}

Note Note::noteFromKey(int key)
{
    Note note;
    note.setPitch((Note::Pitch)(key % 12));
    note.setOctave(-1 + key / 12);
    return note;
}

QString Note::pitchName(Note::Pitch pitch)
{
    switch (pitch) {
    case Pitch::C:   return "do";
    case Pitch::Cis: return "di";
    case Pitch::D:   return "re";
    case Pitch::Ees: return "me";
    case Pitch::E:   return "mi";
    case Pitch::F:   return "fa";
    case Pitch::Fis: return "fi";
    case Pitch::G:   return "so";
    case Pitch::Aes: return "lu";
    case Pitch::A:   return "la";
    case Pitch::Bes: return "se";
    case Pitch::B:   return "si";
    default: break;
    }
    return "?";
}

QString Note::pitchName() const
{
    return pitchName(pitch_);
}

bool Note::isFilled() const
{
    switch (pitch_) {
    case Pitch::C:
    case Pitch::D:
    case Pitch::E:
    case Pitch::Fis:
    case Pitch::Aes:
    case Pitch::Bes:
        return true;
    default:
        break;
    }
    return false;
}

Note::Pitch Note::pitch() const
{
    return pitch_;
}

void Note::setPitch(const Pitch &pitch)
{
    pitch_ = pitch;
}

int Note::octave() const
{
    return octave_;
}

void Note::setOctave(int octave)
{
    octave_ = octave;
}

bool Note::operator==(const Note &other) const
{
    return pitch_ == other.pitch_ && octave_ == other.octave_;
}

bool Note::operator<(const Note &other) const
{
    return octave_ < other.octave_ ||
            (octave_ == other.octave_ && pitch_ < other.pitch_);
}

uint qHash(Note note)
{
    return ::qHash((int)note.pitch()) ^ ::qHash(note.octave());
}

