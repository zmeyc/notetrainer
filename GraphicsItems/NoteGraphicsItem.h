#ifndef NOTEGRAPHICSITEM_H
#define NOTEGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QImage>
#include "Data/Note.h"

class NoteGraphicsItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit NoteGraphicsItem(QGraphicsItem *parent = nullptr);

    Note note() const;
    void setNote(Note note);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

signals:

public slots:

protected:
    QImage noteImage() const;

    Note note_ = Note::C;
    QImage filledNoteImage_;
    QImage hollowNoteImage_;
};

#endif // NOTEGRAPHICSITEM_H
