#include "colourwheel.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QMouseEvent>

ColourWheel::ColourWheel(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(parent);

    layout->addWidget(this);
}

void ColourWheel::setIndicatorColour(const QColor& indicatorColour)
{
    indicatorColour_ = indicatorColour;

    update();
}

QColor ColourWheel::indicatorColour() const
{
    return indicatorColour_;
}

QRect ColourWheel::wheelRect() const
{
    int wheelWidth = 300;
    int wheelHeight = 300;
    return QRect(0, 0, wheelWidth, wheelHeight);
}

int ColourWheel::wheelRectBuffer() const
{
    return 10;
}

QPoint ColourWheel::indicatorColourPos() const
{
    double h = indicatorColour_.hslHueF();

    double t = (h * 2 - 1) * M_PI;

    double s = indicatorColour_.hslSaturationF();

    double fx = std::sin(-t) * s;
    double fy = std::cos(t) * s;

    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();
    double x = (fx * 0.5 + 0.5) * wheel.width() + wheelBuffer;
    double y = (fy * 0.5 + 0.5) * wheel.height() + wheelBuffer;

    return QPoint(x, y);
}

QColor ColourWheel::colourFromPoint(const QPoint& point) const
{
    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();
    int totalWidth = wheel.width() + wheelBuffer * 2;
    int totalHeight = wheel.height() + wheelBuffer * 2;

    QPoint drawPos = geometry().center();
    drawPos.setX(drawPos.x() - totalWidth / 2);
    drawPos.setY(drawPos.y() - totalHeight / 2);

    QPoint imagePoint = point - drawPos;

    double fx = (imagePoint.x() - wheelBuffer) / double(wheel.width()) * 2 - 1;
    double fy = (imagePoint.y() - wheelBuffer) / double(wheel.height()) * 2 - 1;

    double s = std::hypot(fx, fy);

    double t = std::atan2(-fx, fy);

    QColor windowColour = palette().window().color();

    QColor colour = windowColour;

    double h = t / M_PI * 0.5 + 0.5;

    double aa = 1;

    if (s > 1)
    {
        colour.setHslF(h, 1, 0.5);

        s -= 1;

        aa = 1 / (1 + s * s * 100000);
    }
    else
    {
        colour.setHslF(h, s, 0.5);
    }

    colour.setRedF(colour.redF() * aa + windowColour.redF() * (1 - aa));
    colour.setGreenF(colour.greenF() * aa + windowColour.greenF() * (1 - aa));
    colour.setBlueF(colour.blueF() * aa + windowColour.blueF() * (1 - aa));

    return colour;
}

void ColourWheel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();
    int totalWidth = wheel.width() + wheelBuffer * 2;
    int totalHeight = wheel.height() + wheelBuffer * 2;

    QImage image(totalWidth, totalHeight, QImage::Format_RGB888);

    QPoint drawPos = geometry().center();
    drawPos.setX(drawPos.x() - totalWidth / 2);
    drawPos.setY(drawPos.y() - totalHeight / 2);

    for (int y = 0; y < totalHeight; y++)
    {
        for (int x = 0; x < totalWidth; x++)
        {
            QPoint imagePoint = drawPos + QPoint(x, y);

            QColor colour = colourFromPoint(imagePoint);

            image.setPixelColor(x, y, colour);
        }
    }

    painter.drawImage(drawPos, image);

    // Draw indicator

    painter.setRenderHint(QPainter::Antialiasing, true);

    QPoint indicatorPos = drawPos + indicatorColourPos();

    // Line
    QPoint wheelCenterPos = drawPos + QPoint(totalWidth / 2, totalHeight / 2);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(wheelCenterPos, indicatorPos);

    // Black border
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawEllipse(indicatorPos, 10, 10);

    // White interior
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawEllipse(indicatorPos, 8, 8);

    // Colour interior
    painter.setPen(Qt::white);
    painter.setBrush(indicatorColour_);
    painter.drawEllipse(indicatorPos, 7, 7);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

void ColourWheel::mousePressEvent(QMouseEvent *event)
{
    mouseDown_ = true;

    QColor colour = colourFromPoint(event->pos());

    setIndicatorColour(colour);

    emit wheelColourChanged();
}

void ColourWheel::mouseReleaseEvent(QMouseEvent*)
{
    mouseDown_ = false;
}

void ColourWheel::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDown_)
    {
        QColor colour = colourFromPoint(event->pos());

        setIndicatorColour(colour);

        emit wheelColourChanged();
    }
}
