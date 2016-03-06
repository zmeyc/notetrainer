// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QPainter>
#include "StaffGraphicsItem.h"
#include "Utils/Utils.h"

const int staffWidth = 200;
const int octaveCount = 2;
const int ledgerInterval = 15;

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    contentMargins_ = QMargins(10, 10, 10, 10);
}

QRectF StaffGraphicsItem::boundingRect() const
{
    QSize size;
    size.setWidth(staffWidth);
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
    int startY = rect.y() + contentMargins_.top() + ledgerInterval;;
    int atY = startY;
    painter->save();
    painter->setPen(Qt::black);

    for (int octave = 0; octave < octaveCount; ++octave) {
        for (int ledger = 0; ledger < 2; ++ledger) {
            painter->drawLine(leftX,
                              atY,
                              rightX,
                              atY);
            atY += ledgerInterval;
        }
        atY += ledgerInterval;
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
