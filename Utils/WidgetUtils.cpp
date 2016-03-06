// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QWidget>
#include <QPalette>
#include "WidgetUtils.h"

WidgetUtils::WidgetUtils()
{

}

void WidgetUtils::setBackgroundColor(QWidget *widget, const QColor &color)
{
    QPalette pal(widget->palette());
    pal.setColor(QPalette::Background, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
}
