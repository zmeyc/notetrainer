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

    void setOctaveRange(int fromOctave, int toOctave);
    void addNote(const Note &note);
    void removeNote(const Note &note);
    void removeAllNotes();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
signals:

public slots:

protected:
    void updateNotePositions();

    QMargins contentMargins_;
    int fromOctave_ = 0;
    int toOctave_ = 0;
};

#endif // STAFFGRAPHICSITEM_H
