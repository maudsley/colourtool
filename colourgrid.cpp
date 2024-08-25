#include "colourgrid.h"
#include <QPainter>

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

void ColourGrid::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QRect gridRect = rect();

    const int tileWidth = 16;
    const int tileHeight = (tileWidth * 3) / 4;

    int xcount = gridRect.width() / tileWidth;
    xcount += 1; // Round up

    int ycount = gridRect.height() / tileHeight;
    ycount += 1; // Round up

    for (int y = 0; y < ycount; y++)
    {
        for (int x = 0; x < xcount; x++)
        {
            const double fx = x / double(xcount - 1);
            const double fy = y / double(ycount - 1);

            int xpos = x * tileWidth;
            int ypos = y * tileHeight;

            QRect tile(xpos, ypos, tileWidth, tileHeight);

            QColor tileColour = colour_;

            double h1 = std::max(tileColour.hueF() - 0.1, 0.0);
            double h2 = std::min(tileColour.hueF() + 0.1, 1.0);

            double h = h1 * (1 - fx) + h2 * fx;
            double s = tileColour.saturationF();

            tileColour.setHslF(h, s, fx);

            painter.fillRect(tile, tileColour);

            painter.setPen(Qt::black);
            painter.drawRect(tile);
        }
    }
}
