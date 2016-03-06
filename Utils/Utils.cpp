// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QString>
#include <QPoint>
#include <QPointF>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>
#include "Utils.h"

QTextStream stdoutStream(stdout);
QTextStream stderrStream(stderr);
QMutex logMutex;

QTextStream &operator<<(QTextStream &s, const QPoint &p)
{
    return s << QString("(%1, %2)").arg(p.x()).arg(p.y());
}

QTextStream &operator<<(QTextStream &s, const QPointF &p)
{
    return s << QString("(%1, %2)").arg(p.x()).arg(p.y());
}

QTextStream &operator<<(QTextStream &s, const QSizeF &sz)
{
    return s << QString("(%1, %2)").arg(sz.width()).arg(sz.height());
}

QTextStream &operator<<(QTextStream &s, const QSize &sz)
{
    return s << QString("(%1, %2)").arg(sz.width()).arg(sz.height());
}

QTextStream &operator<<(QTextStream &s, const QRect &r)
{
    return s << "{ " << r.topLeft() << ", " << r.size() << " }";
}

QTextStream &operator<<(QTextStream &s, const QRectF &r)
{
    return s << "{ " << r.topLeft() << " " << r.size() << " }";
}
