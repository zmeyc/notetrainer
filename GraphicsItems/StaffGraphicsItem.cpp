// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QPainter>
#include <QGraphicsScene>
#include "StaffGraphicsItem.h"
#include "NoteGraphicsItem.h"
#include "Utils/Utils.h"

const int staffWidth = 200;
const int ledgerInterval = 20;
const int octaveHeight = ledgerInterval * 3;

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    contentMargins_ = QMargins(10, 10, 10, 10);
}

void StaffGraphicsItem::setOctaveRange(int fromOctave, int toOctave)
{
    if (fromOctave_ != fromOctave || toOctave_ != toOctave)
        update();

    fromOctave_ = fromOctave;
    toOctave_ = toOctave;
}

void StaffGraphicsItem::addNote(const Note &note)
{
    NoteGraphicsItem *noteItem = new NoteGraphicsItem;
    noteItem->setNote(note);
    noteItem->setParentItem(this);
    if (fromOctave_ > note.octave()) {
        fromOctave_ = note.octave();
        update();
    }
    if (toOctave_ < note.octave()) {
        toOctave_ = note.octave();
        update();
    }
    updateNotePositions();
}

void StaffGraphicsItem::removeNote(const Note &note)
{
    foreach (QGraphicsItem *item, childItems()) {
        NoteGraphicsItem *noteItem = dynamic_cast<NoteGraphicsItem *>(item);
        if (!noteItem)
            continue;
        if (noteItem->note() == note)
            scene()->removeItem(noteItem);
    }
}

void StaffGraphicsItem::removeAllNotes()
{
    foreach (QGraphicsItem *item, childItems()) {
        NoteGraphicsItem *noteItem = dynamic_cast<NoteGraphicsItem *>(item);
        if (!noteItem)
            continue;
        scene()->removeItem(noteItem);
    }
}

QRectF StaffGraphicsItem::boundingRect() const
{
    QSize size;
    size.setWidth(staffWidth);
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
            } else {
                painter->drawLine(rect.center().x() - 20,
                                  atY,
                                  rect.center().x() + 20,
                                  atY);
            }
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
    painter->restore();
}

void StaffGraphicsItem::updateNotePositions()
{
    QRectF rect = boundingRect();

    foreach (QGraphicsItem *item, childItems()) {
        NoteGraphicsItem *noteItem = dynamic_cast<NoteGraphicsItem *>(item);
        if (!noteItem)
            continue;
        Note note = noteItem->note();
        int spacePerNote = octaveHeight / 12;
        int octaveIndex = note.octave() - fromOctave_;
        int bottomY = rect.y() + contentMargins_.top() + (octaveIndex + 1) * octaveHeight;
        int atY = bottomY - spacePerNote * (int)note.pitch();
        noteItem->setPos(rect.center().x(), atY);
    }
}
