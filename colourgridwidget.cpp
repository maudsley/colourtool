#include "colourgridwidget.h"
#include <QVBoxLayout>
#include <QFrame>

ColourGridWidget::ColourGridWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Related Colours");
    setFeatures(QDockWidget::DockWidgetFloatable);

    colourGrid_ = new ColourGrid();
    connect(colourGrid_, &ColourGrid::onColourSelected, this, &ColourGridWidget::onColourSelected);

    setWidget(colourGrid_);
}

QColor ColourGridWidget::colour() const
{
    return colourGrid_->colour();
}

void ColourGridWidget::setColour(const QColor& colour)
{
    colourGrid_->setColour(colour);
}
