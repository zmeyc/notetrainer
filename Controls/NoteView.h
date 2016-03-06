// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QGraphicsView>

class NoteView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit NoteView(QWidget *parent = 0);

    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // NOTEVIEW_H
