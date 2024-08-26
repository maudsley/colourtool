#include "colourgrid.h"
#include <QPainter>
#include <QMouseEvent>

ColourGrid::ColourGrid(QWidget *parent)
    : QWidget{parent}
{
    setMinimumHeight(100);
}

QColor ColourGrid::colour() const
{
    return colour_;
}

void ColourGrid::setColour(const QColor& colour)
{
    colour_ = colour;

    update();
}

QSize ColourGrid::getTileSize() const
{
    const int tileWidth = 16;
    const int tileHeight = (tileWidth * 3) / 4;

    return QSize(tileWidth, tileHeight);
}

QColor ColourGrid::pointToColour(const QPoint& point) const
{
    QSize tileSize = getTileSize();
    int px = point.x() / tileSize.width();
    int py = point.y() / tileSize.height();

    const int columnCount = 6;

    int wx = px / columnCount;
    int hx = px % columnCount;
    int nx = wx + hx;
    int ny = 1000 - py * 20;

    if (ny < 0)
    {
        ny = 0;
    }

    QColor colour = colour_;

    int newHue = (colour.hslHue() + nx * 10) % 360;
    int newSaturation = ny % 256;
    int newLightness = ny % 256;

    colour.setHsl(newHue, newSaturation, newLightness);

    return colour;
}

void ColourGrid::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QRect gridRect = rect();

    QSize tileSize = getTileSize();

    int xcount = gridRect.width() / tileSize.width();
    xcount += 1; // Round up

    int ycount = gridRect.height() / tileSize.height();
    ycount += 1; // Round up

    for (int y = 0; y < ycount; y++)
    {
        for (int x = 0; x < xcount; x++)
        {
            QPoint point = QPoint(x * tileSize.width(), y * tileSize.height());

            QRect tile = QRect(point.x(), point.y(), tileSize.width(), tileSize.height());

            QColor colour = pointToColour(point);

            painter.fillRect(tile, colour);

            painter.setPen(Qt::black);
            painter.drawRect(tile);
        }
    }
}

void ColourGrid::mousePressEvent(QMouseEvent *event)
{
    QColor colour = pointToColour(event->pos());

    emit onColourSelected(colour);
}
