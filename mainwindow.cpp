#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colourwheel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ColourTool");

    baseColourWidget_ = new BaseColourWidget();
    connect(baseColourWidget_, &BaseColourWidget::baseColourChanged, this, &MainWindow::handleBaseColourChanged);
    addDockWidget(Qt::LeftDockWidgetArea, baseColourWidget_);

    favouritesWidget_ = new FavouritesWidget();
    addDockWidget(Qt::RightDockWidgetArea, favouritesWidget_);

    colourWheelDisplay_ = new ColourWheelDisplay(ui->widget);
    connect(colourWheelDisplay_, &ColourWheelDisplay::wheelColourDisplayChanged, this, &MainWindow::handleWheelColourChanged);

    ColourWheelIndicators indicators;
    std::vector<QColor> defaultColours;
    for (int i = 0; i < 5; i++)
    {
        QColor defaultColour;
        defaultColour.setHsl(rand() % 255, rand() % 255, 128);
        defaultColours.push_back(defaultColour);
    }
    indicators.setColours(defaultColours);
    indicators.setSelectedIndicator(0);
    colourWheelDisplay_->setDisplayIndicators(indicators);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleBaseColourChanged()
{
    QColor colour = baseColourWidget_->baseColour();

    ColourWheelIndicators indicators = colourWheelDisplay_->displayIndicators();
    indicators.setActiveIndicatorColour(colour);
    colourWheelDisplay_->setDisplayIndicators(indicators);
}

void MainWindow::handleWheelColourChanged()
{
    ColourWheelIndicators indicators = colourWheelDisplay_->displayIndicators();
    std::optional<QColor> wheelColour = indicators.activeIndicatorColour();

    if (wheelColour)
    {
        baseColourWidget_->setSliderColours(wheelColour.value());
    }
}
