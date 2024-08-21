#include "colourslider.h"
#include <QVBoxLayout>
#include <QMouseEvent>

ColourSlider::ColourSlider(QWidget *parent)
    : QWidget{parent}
{
//    QVBoxLayout* outerLayout = new QVBoxLayout(parent); // Replace layout of parent window
//    outerLayout->setContentsMargins(0, 0, 0, 0);
//    outerLayout->setSpacing(0);

    QVBoxLayout* innerLayout = new QVBoxLayout(this);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setSpacing(0);

    //outerLayout->addWidget(this); // Add ourself to parent layout

    bar_ = new ColourSliderBar();
    innerLayout->addWidget(bar_);

    indicator_ = new ColourSliderIndicator();
    innerLayout->addWidget(indicator_);

    setMouseTracking(true);
}

QColor ColourSlider::sliderColour() const
{
    double pos = indicator_->indicatorPosition();

    QColor colour = bar_->colourBarSamplerDelegate()->getColourAtPosition(pos);

    return colour;
}

void ColourSlider::setColourSamplerDelegate(const std::shared_ptr<ColourSamplerDelegate>& colourSamplerDelegate)
{
    bar_->setColourBarSamplerDelegate(colourSamplerDelegate);

    indicator_->setIndicatorPosition(colourSamplerDelegate->getPosition());
}

std::shared_ptr<ColourSamplerDelegate> ColourSlider::colourBarSamplerDelegate() const
{
    std::shared_ptr<ColourSamplerDelegate> delegate = bar_->colourBarSamplerDelegate();

    return delegate;
}

void ColourSlider::setSliderPosFromPoint(const QPoint& point)
{
    QRect slider = bar_->sliderGeometry();

    int indicatorWidth = indicator_->indicatorRect().width();

    int localPos = point.x() - slider.left() - indicatorWidth / 2;

    double pos = localPos / double(slider.width());

    if (pos < 0)
    {
        pos = 0;
    }
    else if (pos > 1)
    {
        pos = 1;
    }

    indicator_->setIndicatorPosition(pos);

    emit indicatorMoved();
}

void ColourSlider::mousePressEvent(QMouseEvent *event)
{
    mouseDown_ = true;

    setSliderPosFromPoint(event->pos());
}

void ColourSlider::mouseReleaseEvent(QMouseEvent*)
{
    mouseDown_ = false;
}

void ColourSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDown_)
    {
        setSliderPosFromPoint(event->pos());
    }
}
