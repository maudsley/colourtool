#include "colourrectanglewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

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

void ColourRectangleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragStartPosition_ = event->pos();
    }
}

void ColourRectangleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        double dist = (event->pos() - dragStartPosition_).manhattanLength();
        if (dist >= QApplication::startDragDistance())
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            mimeData->setColorData(colour_);

            drag->setMimeData(mimeData);

            QPixmap icon(32, 32);
            icon.fill(colour_);
            drag->setPixmap(icon);

            drag->exec(Qt::CopyAction);
        }
    }
}
