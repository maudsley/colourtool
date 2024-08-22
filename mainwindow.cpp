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

    colourWheel_ = new ColourWheel(ui->widget);
    connect(colourWheel_, &ColourWheel::wheelColourChanged, this, &MainWindow::handleWheelColourChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleBaseColourChanged()
{
    QColor colour = baseColourWidget_->baseColour();

    colourWheel_->setIndicatorColour(colour);
}

void MainWindow::handleWheelColourChanged()
{
    QColor colour = colourWheel_->indicatorColour();

    baseColourWidget_->setSliderColours(colour);
}
