#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colourslider.h"
#include "rgbcoloursampler.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* widgetLayout = new QVBoxLayout(ui->widget);
    widgetLayout->setContentsMargins(0, 0, 0, 0);
    widgetLayout->setSpacing(0);

    colourRectangle_ = new ColourRectangleWidget();
    widgetLayout->addWidget(colourRectangle_);

    widgetLayout->addSpacing(10);

    redSlider_ = new ColourSlider();
    connect(redSlider_, &ColourSlider::indicatorMoved, this, &MainWindow::handleRedSliderChanged);
    widgetLayout->addWidget(redSlider_);

    greenSlider_ = new ColourSlider();
    connect(greenSlider_, &ColourSlider::indicatorMoved, this, &MainWindow::handleGreenSliderChanged);
    widgetLayout->addWidget(greenSlider_);

    blueSlider_ = new ColourSlider();
    connect(blueSlider_, &ColourSlider::indicatorMoved, this, &MainWindow::handleBlueSliderChanged);
    widgetLayout->addWidget(blueSlider_);

    widgetLayout->addStretch();

    setSliderColours(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSliderColours(const QColor& colour)
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

void MainWindow::handleRedSliderChanged()
{
    QColor updatedColour = redSlider_->sliderColour();

    setSliderColours(updatedColour);
}

void MainWindow::handleGreenSliderChanged()
{
    QColor updatedColour = greenSlider_->sliderColour();

    setSliderColours(updatedColour);
}

void MainWindow::handleBlueSliderChanged()
{
    QColor updatedColour = blueSlider_->sliderColour();

    setSliderColours(updatedColour);
}
