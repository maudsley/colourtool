#include "colourwheeldisplay.h"
#include "frameseperator.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QLabel>

ColourWheelDisplay::ColourWheelDisplay(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus); // Let this widget take focus

    QVBoxLayout* outerLayout = new QVBoxLayout(parent);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    QToolBar* toolBar = new QToolBar(this);
    toolBar->setIconSize(QSize(16, 16));
    QAction* plusAction = toolBar->addAction(QIcon(":/icons/cplus.png"), "Add Indicator");
    connect(plusAction, &QAction::triggered, this, &ColourWheelDisplay::handleAddIndicator);
    QAction* minusAction = toolBar->addAction(QIcon(":/icons/cminus.png"), "Remove Indicator");
    connect(minusAction, &QAction::triggered, this, &ColourWheelDisplay::handleRemoveIndicator);

    QHBoxLayout* titleLayout = new QHBoxLayout();
    outerLayout->addLayout(titleLayout);
    QLabel* titleLabel = new QLabel("Colour Selection");
    titleLabel->setStyleSheet("QLabel { background: lightgray; }");
    titleLabel->setContentsMargins(3, 0, 3, 3);
    titleLayout->addWidget(titleLabel);

    outerLayout->addWidget(toolBar);
    outerLayout->addWidget(new FrameSeperator(""));
    outerLayout->addWidget(this);

    QVBoxLayout* innerLayout = new QVBoxLayout(this);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setSpacing(0);

    colourWheel_ = new ColourWheel();
    connect(colourWheel_, &ColourWheel::wheelColourChanged, this, &ColourWheelDisplay::wheelDisplayChanged);
    innerLayout->addWidget(colourWheel_);

    colourGalleryWidget_ = new ColourGalleryWidget();
    connect(colourGalleryWidget_, &ColourGalleryWidget::galleryIndicatorSelectionChanged, this, &ColourWheelDisplay::galleryIndicatorSelectionChanged);
    innerLayout->addWidget(colourGalleryWidget_);

    innerLayout->setStretch(0, 3);
    innerLayout->setStretch(1, 1);
}

void ColourWheelDisplay::setDisplayIndicators(const ColourWheelIndicators& indicators)
{
    colourWheel_->setIndicators(indicators);
    colourGalleryWidget_->setGalleryIndicators(indicators);
}

ColourWheelIndicators ColourWheelDisplay::displayIndicators() const
{
    // Use colour wheel indicators instead of gallery indicators

    return colourWheel_->indicators();
}

void ColourWheelDisplay::wheelDisplayChanged()
{
    // Copy indicators to the gallery when they are updated by the wheel

    colourGalleryWidget_->setGalleryIndicators(colourWheel_->indicators());

    emit wheelColourDisplayChanged();
}

void ColourWheelDisplay::galleryIndicatorSelectionChanged()
{
    // Copy indicators from the gallery to the wheel

    colourWheel_->setIndicators(colourGalleryWidget_->galleryIndicators());

    emit wheelColourDisplayChanged();
}

void ColourWheelDisplay::handleAddIndicator()
{
    ColourWheelIndicators indicators = colourWheel_->indicators();
    std::vector<QColor> colours = indicators.colours();

    QColor newColour;
    newColour.setHsl(rand() % 359, rand() % 255, 128);

    colours.push_back(newColour); // Add new indicator
    indicators.setColours(colours);
    indicators.setSelectedIndicator(colours.size() - 1);

    colourWheel_->setIndicators(indicators);
    colourGalleryWidget_->setGalleryIndicators(indicators);

    emit wheelColourDisplayChanged();
}

void ColourWheelDisplay::handleRemoveIndicator()
{
    ColourWheelIndicators indicators = colourWheel_->indicators();
    std::vector<QColor> colours = indicators.colours();

    if (colours.size() > 1) // Must have at least one indicator
    {
        colours.pop_back();
        indicators.setColours(colours);
        indicators.setSelectedIndicator(colours.size() - 1);

        colourWheel_->setIndicators(indicators);
        colourGalleryWidget_->setGalleryIndicators(indicators);

        emit wheelColourDisplayChanged();
    }
}
