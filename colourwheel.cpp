#include "colourwheel.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QMouseEvent>

ColourWheel::ColourWheel(QWidget *parent)
    : QWidget{parent}
{
    wheelImage_ = drawWheelImage();
}

void ColourWheel::setIndicators(const ColourWheelIndicators& indicators)
{
    indicators_ = indicators;

    update();
}

ColourWheelIndicators ColourWheel::indicators() const
{
    return indicators_;
}

QRect ColourWheel::wheelRect() const
{
    QRect wheel = rect();

    int size = std::min(wheel.width(), wheel.height());

    double scale = 0.9;

    int wheelWidth = size * scale;
    int wheelHeight = size * scale;

    return QRect(0, 0, wheelWidth, wheelHeight);
}

int ColourWheel::wheelRectBuffer() const
{
    return 10;
}

QImage ColourWheel::drawWheelImage() const
{
    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();
    int totalWidth = wheel.width() + wheelBuffer * 2;
    int totalHeight = wheel.height() + wheelBuffer * 2;

    QImage image(totalWidth, totalHeight, QImage::Format_RGB888);

    for (int y = 0; y < totalHeight; y++)
    {
        for (int x = 0; x < totalWidth; x++)
        {
            QPoint imagePoint = QPoint(x, y);

            QColor colour = colourFromImagePoint(imagePoint);

            image.setPixelColor(x, y, colour);
        }
    }

    return image;
}

QPoint ColourWheel::pointFromColour(const QColor& colour) const
{
    double h = colour.hslHueF();

    double t = (h * 2 - 1) * M_PI;

    double s = colour.hslSaturationF();

    double fx = std::sin(-t) * s;
    double fy = std::cos(t) * s;

    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();
    double x = (fx * 0.5 + 0.5) * wheel.width() + wheelBuffer;
    double y = (fy * 0.5 + 0.5) * wheel.height() + wheelBuffer;

    QPoint drawPos = rect().center();
    drawPos.setX(drawPos.x() - wheelImage_.width() / 2);
    drawPos.setY(drawPos.y() - wheelImage_.height() / 2);

    QPoint result = QPoint(x,y) + drawPos;

    return result;
}

QColor ColourWheel::colourFromWidgetPoint(const QPoint& point) const
{
    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();
    int totalWidth = wheel.width() + wheelBuffer * 2;
    int totalHeight = wheel.height() + wheelBuffer * 2;

    QPoint drawPos = rect().center();
    drawPos.setX(drawPos.x() - totalWidth / 2);
    drawPos.setY(drawPos.y() - totalHeight / 2);

    QPoint imagePoint = point - drawPos;

    QColor result = colourFromImagePoint(imagePoint);

    return result;
}

QColor ColourWheel::colourFromImagePoint(const QPoint& point) const
{
    QRect wheel = wheelRect();
    int wheelBuffer = wheelRectBuffer();

    double fx = (point.x() - wheelBuffer) / double(wheel.width()) * 2 - 1;
    double fy = (point.y() - wheelBuffer) / double(wheel.height()) * 2 - 1;

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

    QPoint drawPos = rect().center();
    drawPos.setX(drawPos.x() - wheelImage_.width() / 2);
    drawPos.setY(drawPos.y() - wheelImage_.height() / 2);

    painter.drawImage(drawPos, wheelImage_);

    // Draw indicators

    painter.setRenderHint(QPainter::Antialiasing, true);

    std::vector<QColor> indicatorColours = indicators_.colours();

    std::optional<size_t> selectedColour = indicators_.selectedIndicator();

    for (size_t i = 0; i < indicatorColours.size(); i++)
    {
        bool selected = false;

        if (selectedColour)
        {
            if (selectedColour.value() == i)
            {
                selected = true;
            }
        }

        QColor indicatorColour = indicatorColours.at(i);

        QPoint indicatorPos = pointFromColour(indicatorColour);

        // Draw connecting line

        QPoint wheelCenterPos = drawPos + QPoint(wheelImage_.width() / 2, wheelImage_.height() / 2);
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(wheelCenterPos, indicatorPos);

        if (selected) // Bigger when selected
        {
            // Draw border

            painter.setPen(Qt::black);
            painter.setBrush(Qt::white);
            painter.drawEllipse(indicatorPos, 11, 11);

            // Draw colour interior

            painter.setPen(Qt::black);
            painter.setBrush(indicatorColour);
            painter.drawEllipse(indicatorPos, 8, 8);
        }
        else
        {
            // Draw border

            painter.setPen(Qt::black);
            painter.setBrush(Qt::white);
            painter.drawEllipse(indicatorPos, 8, 8);

            // Draw colour interior

            painter.setPen(Qt::black);
            painter.setBrush(indicatorColour);
            painter.drawEllipse(indicatorPos, 5, 5);
        }


    }

    painter.setRenderHint(QPainter::Antialiasing, false);
}

void ColourWheel::mousePressEvent(QMouseEvent *event)
{
    std::vector<QColor> indicatorColours = indicators_.colours();

    std::optional<size_t> selectedIndicatorColour;

    for (size_t i = 0; i < indicatorColours.size(); i++)
    {
        QColor colour = indicatorColours.at(i);

        QPoint point = pointFromColour(colour);

        QPoint pointMouseDelta = point - event->pos();

        double dist = std::hypot(pointMouseDelta.x(), pointMouseDelta.y());

        if (dist < 8.0)
        {
            selectedIndicatorColour = i; // Selection changed

            break;
        }
    }

    if (selectedIndicatorColour)
    {
        mouseDown_ = true;

        indicators_.setSelectedIndicator(selectedIndicatorColour);

        update();

        emit wheelColourChanged();
    }
    else
    {
        mouseDown_ = false;
    }
}

void ColourWheel::mouseReleaseEvent(QMouseEvent*)
{
    mouseDown_ = false;
}

void ColourWheel::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDown_)
    {
        std::vector<QColor> indicatorColours = indicators_.colours();

        std::optional<size_t> selectedIndicatorColour = indicators_.selectedIndicator();

        if (selectedIndicatorColour)
        {
            QColor newColour = colourFromWidgetPoint(event->pos());

            indicatorColours[selectedIndicatorColour.value()] = newColour;

            indicators_.setColours(indicatorColours);
        }

        update();

        emit wheelColourChanged();
    }
}

void ColourWheel::resizeEvent(QResizeEvent*)
{
    wheelImage_ = drawWheelImage();

    update();
}
