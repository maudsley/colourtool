#include "colourrectanglewidget.h"
#include <QPainter>

ColourRectangleWidget::ColourRectangleWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedHeight(80);
}

void ColourRectangleWidget::setColour(const QColor& colour)
{
    colour_ = colour;

    update();
}

QColor ColourRectangleWidget::colour() const
{
    return colour_;
}

void ColourRectangleWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QRect mainRect = rect();
    mainRect.adjust(0, 0, -1, -1);
    painter.setPen(Qt::gray);
    painter.fillRect(mainRect, Qt::gray);

    mainRect.adjust(0, 0, -1, -1);

    painter.fillRect(mainRect, colour_);

    QRect outlineRect = rect();
    outlineRect.adjust(0, 0, -3, -3);
    painter.setPen(Qt::black);
    painter.drawRect(outlineRect);
}
