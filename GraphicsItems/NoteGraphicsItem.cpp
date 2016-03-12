#include <QPainter>
#include "NoteGraphicsItem.h"
#include "StaffGraphicsItem.h"
#include "Utils/Utils.h"

#define DEBUG_DRAW 0

NoteGraphicsItem::NoteGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    filledNoteImage_.load(":/Images/filledNote.png");
    hollowNoteImage_.load(":/Images/hollowNote.png");
}

Note NoteGraphicsItem::note() const
{
    return note_;
}

void NoteGraphicsItem::setNote(Note note)
{
    note_ = note;
    update();
}

QRectF NoteGraphicsItem::boundingRect() const
{
    QImage image = noteImage();
    QSizeF size = image.size();
    if (size.isEmpty())
        return QRectF();

    return QRectF(-size.width() / 2, -size.height() / 2,
                  size.width(), size.height()).translated(1, -21);
}

void NoteGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    QImage image = noteImage();
    painter->drawImage(rect.translated(0, 0).topLeft(), image);
    if (showNoteNames()) {
        painter->drawText(rect.bottomRight().x() + 2,
                          rect.bottomRight().y() - 3,
                          note_.pitchName());
    }

#if DEBUG_DRAW
    painter->save();
    painter->setPen(Qt::green);
    painter->drawRect(QRect(-1, -1, 3, 3));
    painter->restore();
#endif
}

QImage NoteGraphicsItem::noteImage() const
{
    QImage image;
    if (note_.isFilled())
        image = filledNoteImage_;
    else
        image = hollowNoteImage_;
    return image;
}

bool NoteGraphicsItem::showNoteNames() const
{
    StaffGraphicsItem *staff = dynamic_cast<StaffGraphicsItem *>(parentItem());
    if (staff && staff->showNoteNames())
        return true;
    return false;
}
