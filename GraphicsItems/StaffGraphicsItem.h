// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef STAFFGRAPHICSITEM_H
#define STAFFGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QMargins>
#include "Data/Note.h"

class StaffGraphicsItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit StaffGraphicsItem(QGraphicsItem *parent = nullptr);

    void addNote(Note note, int octave);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
signals:

public slots:

protected:
    void updateNotePositions();

    QMargins contentMargins_;
};

#endif // STAFFGRAPHICSITEM_H
