#include "colourwheeldisplay.h"
#include <QVBoxLayout>

ColourWheelDisplay::ColourWheelDisplay(QWidget *parent)
    : QFrame{parent}
{
    //setFrameStyle(QFrame::Panel | QFrame::Raised);

    setFocusPolicy(Qt::StrongFocus); // Let this widget take focus

    QVBoxLayout* outerLayout = new QVBoxLayout(parent);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);
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
