#include "coloursliderindicator.h"
#include <QPainter>

ColourSliderIndicator::ColourSliderIndicator(QWidget *parent)
    : QWidget{parent}
{
    setFixedHeight(10);

    // Pass mouse events to parent
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

QRect ColourSliderIndicator::indicatorRect() const
{
    QRect mainRect = rect();

    int grabWidth = mainRect.height();

    // The grab indicator must hang over the edge slightly so that it can precisely indicate zero on the bar
    int halfGrabWidth = mainRect.height() / 2;

    QRect sliderRect(halfGrabWidth, 0, mainRect.width() - grabWidth, mainRect.height());

    int centerPos = sliderRect.left() + (sliderRect.right() - sliderRect.left()) * position_;

    int grabHeight = mainRect.height() / 2;

    QRect grabRect(0, 0, grabWidth, grabHeight + 1);

    grabRect.moveTo(centerPos - halfGrabWidth, 0);

    grabRect.setBottomLeft(grabRect.bottomLeft() - QPoint(1, 0));

    return grabRect;
}

QRect ColourSliderIndicator::indicatorGeometry() const
{
    QRect grabRect = indicatorRect();

    grabRect.moveTo(geometry().topLeft());

    return grabRect;
}

double ColourSliderIndicator::indicatorPosition() const
{
    return position_;
}

void ColourSliderIndicator::setIndicatorPosition(const double position)
{
    position_ = position;

    update();
}

void ColourSliderIndicator::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QRect grabRect = indicatorRect();

    int center = (grabRect.left() + grabRect.right()) / 2;

    painter.setBrush(QBrush(Qt::black));

    QPen pen = painter.pen();
    painter.setPen(QPen(Qt::black));

    QPolygon polygon;
    polygon.append(QPoint(center, grabRect.top()));
    polygon.append(grabRect.bottomRight());
    polygon.append(grabRect.bottomLeft());

    //painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPolygon(polygon);
    //painter.setRenderHint(QPainter::Antialiasing, false);
}
