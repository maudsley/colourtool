#include "basecolourwidget.h"
#include "rgbcoloursampler.h"
#include "hslcoloursampler.h"
#include "frameseperator.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QAction>

BaseColourWidget::BaseColourWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Base Colour");
    setFeatures(QDockWidget::DockWidgetFloatable);
    setMinimumWidth(220);

    QFrame* centralWidget = new QFrame();
    //centralWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);
    setWidget(centralWidget);

    QVBoxLayout* widgetLayout = new QVBoxLayout(centralWidget);
    //widgetLayout->setContentsMargins(0, 0, 0, 0);
    widgetLayout->setSpacing(5);

    colourRectangle_ = new ColourRectangleWidget();
    widgetLayout->addWidget(colourRectangle_);

    widgetLayout->addSpacing(10);

    // Configure RGB sliders

    redSlider_ = new ColourSlider("R");
    connect(redSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleRedSliderChanged);
    widgetLayout->addWidget(redSlider_);

    greenSlider_ = new ColourSlider("G");
    connect(greenSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleGreenSliderChanged);
    widgetLayout->addWidget(greenSlider_);

    blueSlider_ = new ColourSlider("B");
    connect(blueSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleBlueSliderChanged);
    widgetLayout->addWidget(blueSlider_);

    widgetLayout->addWidget(new FrameSeperator("Adjustments"));

    // Configure HSL sliders

    hueSlider_ = new ColourSlider("H");
    connect(hueSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleHueSliderChanged);
    widgetLayout->addWidget(hueSlider_);

    saturationSlider_ = new ColourSlider("S");
    connect(saturationSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleSaturationSliderChanged);
    widgetLayout->addWidget(saturationSlider_);

    lightnessSlider_ = new ColourSlider("L");
    connect(lightnessSlider_, &ColourSlider::indicatorMoved, this, &BaseColourWidget::handleLightnessSliderChanged);
    widgetLayout->addWidget(lightnessSlider_);

    QHBoxLayout* adjustLayout = new QHBoxLayout();
    widgetLayout->addLayout(adjustLayout);
    adjustLayout->addWidget(new QLabel("Increment:"));

    QToolButton* litIncButton = new QToolButton();
    litIncButton->setIcon(QIcon(":/icons/litinc.png"));
    connect(litIncButton, &QToolButton::clicked, this, &BaseColourWidget::buttonLightnessIncrement);
    adjustLayout->addWidget(litIncButton);

    QToolButton* litDecButton = new QToolButton();
    litDecButton->setIcon(QIcon(":/icons/litdec.png"));
    connect(litDecButton, &QToolButton::clicked, this, &BaseColourWidget::buttonLightnessDecrement);
    adjustLayout->addWidget(litDecButton);

    QToolButton* satIncButton = new QToolButton();
    satIncButton->setIcon(QIcon(":/icons/satinc.png"));
    connect(satIncButton, &QToolButton::clicked, this, &BaseColourWidget::buttonSaturationIncrement);
    adjustLayout->addWidget(satIncButton);

    QToolButton* satDecButton = new QToolButton();
    satDecButton->setIcon(QIcon(":/icons/satdec.png"));
    connect(satDecButton, &QToolButton::clicked, this, &BaseColourWidget::buttonSaturationDecrement);
    adjustLayout->addWidget(satDecButton);

    widgetLayout->addWidget(new FrameSeperator(""));

    // Configure hex value line edit

    QHBoxLayout* hexLayout = new QHBoxLayout();
    QLabel* hexLabel = new QLabel("Hex Value:");
    hexEdit_ = new QLineEdit();
    hexEdit_->setFixedWidth(80);
    connect(hexEdit_, &QLineEdit::editingFinished, this, &BaseColourWidget::handleHexEditChanged);
    hexLayout->addWidget(hexLabel);
    hexLayout->addWidget(hexEdit_);
    hexLayout->setStretch(0, 1);
    widgetLayout->addLayout(hexLayout);

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

    // Configure RGB sliders

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

    // Configure HSL sliders

    std::shared_ptr<HslColourSampler> hueSampler = std::make_shared<HslColourSampler>();
    hueSampler->setChannel(HslColourSampler::ChannelHue);
    hueSampler->setColour(colour);
    hueSlider_->setColourSamplerDelegate(hueSampler);

    std::shared_ptr<HslColourSampler> saturationSampler = std::make_shared<HslColourSampler>();
    saturationSampler->setChannel(HslColourSampler::ChannelSaturation);
    saturationSampler->setColour(colour);
    saturationSlider_->setColourSamplerDelegate(saturationSampler);

    std::shared_ptr<HslColourSampler> lightnessSampler = std::make_shared<HslColourSampler>();
    lightnessSampler->setChannel(HslColourSampler::ChannelLightness);
    lightnessSampler->setColour(colour);
    lightnessSlider_->setColourSamplerDelegate(lightnessSampler);

    // Configure hex value

    hexEdit_->setText(colour.name());
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

void BaseColourWidget::handleHueSliderChanged()
{
    QColor updatedColour = hueSlider_->sliderColour();

    setSliderColours(updatedColour);

    emit baseColourChanged();
}

void BaseColourWidget::handleSaturationSliderChanged()
{
    QColor updatedColour = saturationSlider_->sliderColour();

    setSliderColours(updatedColour);

    emit baseColourChanged();
}

void BaseColourWidget::handleLightnessSliderChanged()
{
    QColor updatedColour = lightnessSlider_->sliderColour();

    setSliderColours(updatedColour);

    emit baseColourChanged();
}

void BaseColourWidget::buttonSaturationIncrement()
{
    QColor colour = colourRectangle_->colour();

    int h;
    int s;
    int l;

    colour.getHsl(&h, &s, &l);

    s += 10;

    colour.setHsl(h, s, l);

    setSliderColours(colour);

    emit baseColourChanged();
}

void BaseColourWidget::buttonSaturationDecrement()
{
    QColor colour = colourRectangle_->colour();

    int h;
    int s;
    int l;

    colour.getHsl(&h, &s, &l);

    s -= 10;

    colour.setHsl(h, s, l);

    setSliderColours(colour);

    emit baseColourChanged();
}

void BaseColourWidget::buttonLightnessIncrement()
{
    QColor colour = colourRectangle_->colour();

    int h;
    int s;
    int l;

    colour.getHsl(&h, &s, &l);

    l += 10;

    colour.setHsl(h, s, l);

    setSliderColours(colour);

    emit baseColourChanged();
}

void BaseColourWidget::buttonLightnessDecrement()
{
    QColor colour = colourRectangle_->colour();

    int h;
    int s;
    int l;

    colour.getHsl(&h, &s, &l);

    l -= 10;

    colour.setHsl(h, s, l);

    setSliderColours(colour);

    emit baseColourChanged();
}

void BaseColourWidget::handleHexEditChanged()
{
    QColor colour(hexEdit_->text());

    setSliderColours(colour);

    emit baseColourChanged();
}
