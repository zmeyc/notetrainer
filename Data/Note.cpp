// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include "Note.h"

QString noteName(Note note)
{
    switch (note) {
    case Note::C:   return "do";
    case Note::Cis: return "di";
    case Note::D:   return "re";
    case Note::Ees: return "me";
    case Note::E:   return "mi";
    case Note::F:   return "fa";
    case Note::Fis: return "fi";
    case Note::G:   return "so";
    case Note::Aes: return "lu";
    case Note::A:   return "la";
    case Note::Bes: return "se";
    case Note::B:   return "si";
    default: break;
    }
    return "?";
}
