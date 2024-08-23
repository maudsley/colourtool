#include "colourgallerywidget.h"
#include <QPainter>

ColourGalleryWidget::ColourGalleryWidget(QWidget *parent)
    : QWidget{parent}
{

}

void ColourGalleryWidget::setGalleryIndicators(const ColourWheelIndicators& indicators)
{
    galleryIndicators_ = indicators;

    update();
}

ColourWheelIndicators ColourGalleryWidget::galleryIndicators() const
{
    return galleryIndicators_;
}

void ColourGalleryWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    std::vector<QColor> colours = galleryIndicators_.colours();

    std::optional<size_t> selectedColour = galleryIndicators_.selectedIndicator();

    int rectSize = 40;

    int rectSpacing = 10;

    int allRectsWidth = colours.size() * (rectSize + rectSpacing);

    for (size_t i = 0; i < colours.size(); i++)
    {
        bool selected = false;

        if (selectedColour)
        {
            if (selectedColour.value() == i)
            {
                selected = true;
            }
        }

        QRect tile(0, 0, rectSize, rectSize);

        tile.translate(i * (rectSize + rectSpacing), 0);

        tile.translate(rect().center() - QPoint(allRectsWidth, rectSize) / 2);

        // Draw tile border

        if (selected)
        {
            painter.fillRect(tile, Qt::white);
            painter.setPen(Qt::black);
            painter.drawRect(tile);
        }
        else
        {
            painter.fillRect(tile, Qt::white);
            painter.setPen(Qt::lightGray);
            painter.drawRect(tile);
        }

        // Draw colour tile interior

        tile.adjust(2, 2, -2, -2);

        painter.fillRect(tile, colours.at(i));
        painter.setPen(colours.at(i).darker());
        painter.drawRect(tile);

        // Draw reflection

        QRect reflection = tile;
        reflection.translate(0, rectSize);
        reflection.setBottom(reflection.bottom() - reflection.height() / 2);

        QColor transparentColour = colours.at(i);
        transparentColour.setAlphaF(0.35);

        QPoint startGradient(reflection.center().x(), reflection.top());
        QPoint stopGradient(reflection.center().x(), reflection.bottom());

        QLinearGradient lgrad(startGradient, stopGradient);
        lgrad.setColorAt(0.0, transparentColour);
        lgrad.setColorAt(1.0, QColor(0,0,0,0));
        painter.fillRect(reflection, lgrad);
    }

}
