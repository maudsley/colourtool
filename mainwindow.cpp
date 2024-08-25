#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colourwheel.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet(R"(
        QMainWindow::separator {
            background: gray;
            width: 1px;
            height: 1px;
        }
        QDockWidget::title {
            background: lightgray;
        }
    )");

    setWindowTitle("ColourTool");

    colourWheelDisplay_ = new ColourWheelDisplay(ui->widget);
    connect(colourWheelDisplay_, &ColourWheelDisplay::wheelColourDisplayChanged, this, &MainWindow::handleWheelColourChanged);

    baseColourWidget_ = new BaseColourWidget();
    connect(baseColourWidget_, &BaseColourWidget::baseColourChanged, this, &MainWindow::handleBaseColourChanged);
    addDockWidget(Qt::LeftDockWidgetArea, baseColourWidget_);

    favouritesWidget_ = new FavouritesWidget();
    addDockWidget(Qt::RightDockWidgetArea, favouritesWidget_);

    colourGridWidget_ = new ColourGridWidget();
    addDockWidget(Qt::BottomDockWidgetArea, colourGridWidget_);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    connect(ui->actionRandom, &QAction::triggered, this, &MainWindow::makeRandomColours);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutInformation);

    makeRandomColours();
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

    colourGridWidget_->setColour(colour);
}

void MainWindow::handleWheelColourChanged()
{
    ColourWheelIndicators indicators = colourWheelDisplay_->displayIndicators();
    std::optional<QColor> wheelColour = indicators.activeIndicatorColour();

    if (wheelColour)
    {
        baseColourWidget_->setSliderColours(wheelColour.value());

        colourGridWidget_->setColour(wheelColour.value());
    }
}

void MainWindow::makeRandomColours()
{
    size_t colourCount = colourWheelDisplay_->displayIndicators().colours().size();

    if (colourCount == 0)
    {
        colourCount = 3;
    }

    ColourWheelIndicators indicators;
    std::vector<QColor> defaultColours;
    for (size_t i = 0; i < colourCount; i++)
    {
        QColor defaultColour;
        defaultColour.setHsl(rand() % 255, rand() % 255, 128);
        defaultColours.push_back(defaultColour);
    }

    indicators.setColours(defaultColours);
    indicators.setSelectedIndicator(0);
    colourWheelDisplay_->setDisplayIndicators(indicators);
    baseColourWidget_->setSliderColours(defaultColours.at(0));
    colourGridWidget_->setColour(defaultColours.at(0));
}

void MainWindow::showAboutInformation()
{
    QString info;
    info += windowTitle();
    QMessageBox::information(this, "About", info);
}
