#include "basecolourwidget.h"
#include "rgbcoloursampler.h"
#include <QVBoxLayout>
#include <QFrame>

BaseColourWidget::BaseColourWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Base Colour");
    setFeatures(QDockWidget::DockWidgetFloatable);
    setMinimumWidth(250);

    QFrame* centralWidget = new QFrame();
    centralWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);
    setWidget(centralWidget);

    QVBoxLayout* widgetLayout = new QVBoxLayout(centralWidget);
    //widgetLayout->setContentsMargins(0, 0, 0, 0);
    //widgetLayout->setSpacing(0);

    colourRectangle_ = new ColourRectangleWidget();
    widgetLayout->addWidget(colourRectangle_);

    widgetLayout->addSpacing(10);

    redSlider_ = new ColourSlider();
    connect(redSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleRedSliderChanged);
    widgetLayout->addWidget(redSlider_);

    greenSlider_ = new ColourSlider();
    connect(greenSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleGreenSliderChanged);
    widgetLayout->addWidget(greenSlider_);

    blueSlider_ = new ColourSlider();
    connect(blueSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleBlueSliderChanged);
    widgetLayout->addWidget(blueSlider_);

    widgetLayout->addStretch();

    setSliderColours(Qt::black);
}

QColor BaseColourWidget::baseColour() const
{
    QColor colour = colourRectangle_->colour();

    return colour;
}

void BaseColourWidget::setSliderColours(const QColor& colour)
{
    colourRectangle_->setColour(colour);

    std::shared_ptr<RgbColourSampler> redSampler = std::make_shared<RgbColourSampler>();
    redSampler->setChannel(RgbColourSampler::ChannelRed);
    redSampler->setColour(colour);
    redSlider_->setColourSamplerDelegate(redSampler);

    std::shared_ptr<RgbColourSampler> greenSampler = std::make_shared<RgbColourSampler>();
    greenSampler->setChannel(RgbColourSampler::ChannelGreen);
    greenSampler->setColour(colour);
    greenSlider_->setColourSamplerDelegate(greenSampler);

    std::shared_ptr<RgbColourSampler> blueSampler = std::make_shared<RgbColourSampler>();
    blueSampler->setChannel(RgbColourSampler::ChannelBlue);
    blueSampler->setColour(colour);
    blueSlider_->setColourSamplerDelegate(blueSampler);
}

void BaseColourWidget::handleRedSliderChanged()
{
    QColor updatedColour = redSlider_->sliderColour();

    setSliderColours(updatedColour);

    emit baseColourChanged();
}

void BaseColourWidget::handleGreenSliderChanged()
{
    QColor updatedColour = greenSlider_->sliderColour();

    setSliderColours(updatedColour);

    emit baseColourChanged();
}

void BaseColourWidget::handleBlueSliderChanged()
{
    QColor updatedColour = blueSlider_->sliderColour();

    setSliderColours(updatedColour);

    emit baseColourChanged();
}
