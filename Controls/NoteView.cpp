// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include "NoteView.h"
#include "Models/NoteViewScene.h"

NoteView::NoteView(QWidget *parent)
    : QGraphicsView(parent)
{
    setBackgroundBrush(Qt::lightGray);
    setViewportUpdateMode(FullViewportUpdate);

    setScene(new NoteViewScene(this));
}

void NoteView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);

    painter->fillRect(sceneRect(), Qt::white);
}
