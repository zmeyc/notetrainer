// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QPainter>
#include <QGraphicsScene>
#include "StaffGraphicsItem.h"
#include "NoteGraphicsItem.h"
#include "Utils/Utils.h"

const int staffExtraWidth = 100;
const int noteHorizontalInterval = 40;
const int ledgerInterval = 20;
const int octaveHeight = ledgerInterval * 3;
const int extraLedgerWidth = 30;

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    contentMargins_ = QMargins(10, 10, 10, 10);
}

void StaffGraphicsItem::setOctaveRange(int fromOctave, int toOctave)
{
    if (fromOctave_ != fromOctave || toOctave_ != toOctave)
        prepareGeometryChange();

    fromOctave_ = fromOctave;
    toOctave_ = toOctave;
}

void StaffGraphicsItem::addNote(int queueIndex, const Note &note, int group)
{
    if (queueIndex < 0 || queueIndex >= noteGroupsQueue_.size())
        return;
    if (fromOctave_ > note.octave())
        return;
    if (toOctave_ < note.octave())
        return;
    NoteGroups &noteGroups = noteGroupsQueue_[queueIndex];
    Notes &notes = noteGroups[group];
    Notes::iterator i = notes.find(note);
    if (i != notes.end())
        return;
    NoteGraphicsItem *noteItem = new NoteGraphicsItem;
    notes[note] = noteItem;
    noteItem->setNote(note);
    noteItem->setParentItem(this);
    updateNotePositions();
}

bool StaffGraphicsItem::hasNote(int queueIndex, const Note &note, int group)
{
    if (queueIndex < 0 || queueIndex >= noteGroupsQueue_.size())
        return false;
    if (fromOctave_ > note.octave())
        return false;
    if (toOctave_ < note.octave())
        return false;
    NoteGroups &noteGroups = noteGroupsQueue_[queueIndex];
    Notes &notes = noteGroups[group];
    Notes::iterator i = notes.find(note);
    if (i == notes.end())
        return false;
    return true;
}

bool StaffGraphicsItem::hasNote(int queueIndex, const Note &note)
{
    if (queueIndex < 0 || queueIndex >= noteGroupsQueue_.size())
        return false;
    if (fromOctave_ > note.octave())
        return false;
    if (toOctave_ < note.octave())
        return false;
    NoteGroups &noteGroups = noteGroupsQueue_[queueIndex];
    foreach (const Notes &notes, noteGroups) {
        Notes::const_iterator i = notes.find(note);
        if (i != notes.end())
            return true;
    }
    return false;
}

void StaffGraphicsItem::queuePop()
{
    if (noteGroupsQueue_.isEmpty())
        return;
    NoteGroups &noteGroups = noteGroupsQueue_[0];
    foreach (const Notes &notes, noteGroups.values()) {
        foreach (NoteGraphicsItem *noteItem, notes.values()) {
            scene()->removeItem(noteItem);
        }
    }
    noteGroupsQueue_.remove(0);
}

int StaffGraphicsItem::queueLength()
{
    return noteGroupsQueue_.size();
}

void StaffGraphicsItem::queuePushNote(const Note &note, int group)
{
    int queueIndex = noteGroupsQueue_.size();
    noteGroupsQueue_.resize(queueIndex + 1);
    addNote(queueIndex, note, group);
    prepareGeometryChange();
}

void StaffGraphicsItem::removeNote(int queueIndex, const Note &note, int group)
{
    if (queueIndex < 0 || queueIndex >= noteGroupsQueue_.size())
        return;
    NoteGroups &noteGroups = noteGroupsQueue_[queueIndex];
    Notes &notes = noteGroups[group];
    Notes::iterator i = notes.find(note);
    if (i == notes.end())
        return;
    NoteGraphicsItem *noteItem = i.value();
    notes.erase(i);
    scene()->removeItem(noteItem);
}

void StaffGraphicsItem::removeAllNotes()
{
    foreach (QGraphicsItem *item, childItems()) {
        NoteGraphicsItem *noteItem = dynamic_cast<NoteGraphicsItem *>(item);
        if (!noteItem)
            continue;
        scene()->removeItem(noteItem);
    }
    noteGroupsQueue_.clear();
}

QRectF StaffGraphicsItem::boundingRect() const
{
    QSize size;
    size.setWidth(notesAreaWidth() + staffExtraWidth);
    int octaveCount = toOctave_ - fromOctave_ + 1;
    size.setHeight(octaveCount * ledgerInterval * 3);
    return QRectF(-size.width() / 2, -size.height() / 2,
                  size.width(), size.height()).marginsAdded(contentMargins_);
}

void StaffGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    int leftX = rect.x() + contentMargins_.left();
    int rightX = rect.x() + rect.width() - contentMargins_.right();
    int startY = rect.y() + contentMargins_.top() + ledgerInterval;
    int atY = startY;
    painter->save();
    painter->setPen(Qt::black);

    for (int octave = fromOctave_; octave <= toOctave_; ++octave) {
        for (int ledger = 0; ledger < 3; ++ledger) {
            if (ledger < 2) {
                painter->drawLine(leftX,
                                  atY,
                                  rightX,
                                  atY);
            } //else {
//                painter->drawLine(rect.center().x() - 20,
//                                  atY,
//                                  rect.center().x() + 20,
//                                  atY);
//            }
            atY += ledgerInterval;
        }
    }    
    painter->drawLine(leftX,
                      startY,
                      leftX,
                      atY - ledgerInterval * 2);
    painter->drawLine(rightX,
                      startY,
                      rightX,
                      atY - ledgerInterval * 2);

    int len = queueLength();
    int atX = rect.center().x() - notesAreaWidth() / 2;
    for (int queueIndex = 0; queueIndex < len; ++queueIndex) {
        atY = startY - 3 * ledgerInterval;
        for (int octave = toOctave_ + 1; octave >= fromOctave_; --octave) {
            atY += 2 * ledgerInterval;
            Note noteCis(Note::Pitch::Cis, octave);
            Note noteC(Note::Pitch::C, octave);
            Note noteB(Note::Pitch::B, octave - 1);
            if (hasNote(queueIndex, noteCis) ||
                    hasNote(queueIndex, noteC) ||
                    hasNote(queueIndex, noteB)) {
                painter->drawLine(atX - extraLedgerWidth / 2,
                                  atY,
                                  atX + extraLedgerWidth / 2,
                                  atY);
            }
            atY += ledgerInterval;
        }
        atX += noteHorizontalInterval;
    }

    painter->restore();
}

int StaffGraphicsItem::notesAreaWidth() const
{
    int horizontalIntervalCount = (int)noteGroupsQueue_.size() - 1;
    if (horizontalIntervalCount < 0)
        horizontalIntervalCount = 0;
    return noteHorizontalInterval * horizontalIntervalCount;
}

void StaffGraphicsItem::updateNotePositions()
{
    QRectF rect = boundingRect();

    int octaveCount = toOctave_ - fromOctave_ + 1;

    int len = queueLength();
    int atX = rect.center().x() - notesAreaWidth() / 2;
    for (int i = 0; i < len; ++i) {
        NoteGroups &noteGroups = noteGroupsQueue_[i];
        foreach (const Notes &notes, noteGroups.values()) {
            foreach (NoteGraphicsItem *noteItem, notes.values()) {
                Note note = noteItem->note();
                int spacePerNote = octaveHeight / 12;
                int octaveIndex = octaveCount - (note.octave() - fromOctave_) - 1;
                int bottomY = rect.y() + contentMargins_.top() +
                        (octaveIndex + 1) * octaveHeight;
                int atY = bottomY - spacePerNote * (int)note.pitch();
                noteItem->setPos(atX, atY);
            }
        }
        atX += noteHorizontalInterval;
    }
}
