#include "coloursliderbar.h"
#include <QPaintEvent>
#include <QPainter>

ColourSliderBar::ColourSliderBar(QWidget *parent)
    : QWidget{parent}
{
    setFixedHeight(20);

    // Pass mouse events to parent
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ColourSliderBar::setColourBarSamplerDelegate(const std::shared_ptr<ColourSamplerDelegate>& colourSamplerDelegate)
{
    colourSamplerDelegate_ = colourSamplerDelegate;

    update();
}

std::shared_ptr<ColourSamplerDelegate> ColourSliderBar::colourBarSamplerDelegate() const
{
    return colourSamplerDelegate_;
}

QRect ColourSliderBar::sliderRect() const
{
    QRect mainRect = rect();

    int grabWidth = mainRect.height() / 3;

    // The grab indicator must hang over the edge slightly so that it can precisely indicate zero on the bar
    int halfGrabWidth = grabWidth / 2;

    QRect sliderRect(halfGrabWidth, 0, mainRect.width() - grabWidth, mainRect.height());

    return sliderRect;
}

QRect ColourSliderBar::sliderGeometry() const
{
    QRect grabRect = sliderRect();

    grabRect.moveTo(geometry().topLeft());

    return grabRect;
}

void ColourSliderBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QRect mainRect = sliderRect();
    mainRect.adjust(0, 0, -1, -1);
    painter.setPen(Qt::gray);
    painter.fillRect(mainRect, Qt::gray);

    mainRect.adjust(0, 0, -1, -1);

    int leftPos = mainRect.left();
    int rightPos = mainRect.right();

    int width = rightPos - leftPos;

    for (int i = 1; i < width; i++)
    {
        double pos = i / double(width - 1);

        QColor colour = Qt::black;

        if (colourSamplerDelegate_)
        {
            colour = colourSamplerDelegate_->getColourAtPosition(pos);
        }

        painter.setPen(colour);

        QPoint topLine(leftPos + i, mainRect.top());
        QPoint bottomLine(leftPos + i, mainRect.bottom());
        painter.drawLine(topLine, bottomLine);
    }

    QRect outlineRect = sliderRect();
    outlineRect.adjust(0, 0, -3, -3);
    painter.setPen(Qt::black);
    painter.drawRect(outlineRect);
}
