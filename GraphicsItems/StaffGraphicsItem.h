// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef STAFFGRAPHICSITEM_H
#define STAFFGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QMargins>

class StaffGraphicsItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit StaffGraphicsItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
signals:

public slots:

protected:
    QMargins contentMargins_;
};

#endif // STAFFGRAPHICSITEM_H
