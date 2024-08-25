#include "colourslider.h"
#include <QGridLayout>
#include <QMouseEvent>
#include <QLabel>

ColourSlider::ColourSlider(const QString& label)
{
    QGridLayout* outerLayout = new QGridLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    QLabel* nameLabel = new QLabel(label);
    outerLayout->addWidget(nameLabel, 0, 0);

    bar_ = new ColourSliderBar();
    outerLayout->addWidget(bar_, 0, 1);

    indicator_ = new ColourSliderIndicator();
    outerLayout->addWidget(indicator_, 1, 1);

    edit_ = new QLineEdit();
    connect(edit_, &QLineEdit::editingFinished, this, &ColourSlider::colourSliderTextChanged);
    outerLayout->addWidget(edit_, 0, 2);
    edit_->setFixedWidth(40);

    outerLayout->setColumnStretch(1, 1);

    setMouseTracking(true);
}

double ColourSlider::sliderValue()
{
    double value = indicator_->indicatorPosition();

    return value;
}

void ColourSlider::setSliderValue(const double value)
{
    indicator_->setIndicatorPosition(value);
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

    double pos = colourSamplerDelegate->getPosition();

    indicator_->setIndicatorPosition(pos);

    const int maxValue = bar_->colourBarSamplerDelegate()->getMaxValue();

    edit_->setText(QString::number(int(pos * maxValue)));
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

    edit_->setText(QString::number(int(pos * 255)));

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

void ColourSlider::colourSliderTextChanged()
{
    const int maxValue = bar_->colourBarSamplerDelegate()->getMaxValue();

    int n = edit_->text().toInt();

    double pos = n / double(maxValue);

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
