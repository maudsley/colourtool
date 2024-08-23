#include "favouriteswidget.h"
#include "favouriteitemwidget.h"
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>
#include <QToolBar>

FavouritesWidget::FavouritesWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Favourite Colours");
    setFeatures(QDockWidget::DockWidgetFloatable);
    setMinimumWidth(250);
    setAcceptDrops(true);

    QWidget* centralWidget = new QWidget();
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    scrollArea_ = new QScrollArea();
    scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(scrollArea_);

    scrollAreaWidget_ = new QWidget();
    scrollArea_->setWidget(scrollAreaWidget_);
    scrollArea_->setWidgetResizable(true);

    layout_ = new QVBoxLayout(scrollAreaWidget_);
    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->setSpacing(1);
    layout_->addStretch();

    QToolBar* toolBar = new QToolBar();
    layout->addWidget(toolBar);
    toolBar->hide();
}

void FavouritesWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasColor())
    {
        event->acceptProposedAction();
    }
}

void FavouritesWidget::dropEvent(QDropEvent *event)
{
    QVariant colourVariant = event->mimeData()->colorData();

    if (colourVariant.canConvert<QColor>())
    {
        QColor colour = colourVariant.value<QColor>();

        FavouriteItemWidget* item = new FavouriteItemWidget(colour);
        layout_->insertWidget(0, item);

        event->acceptProposedAction();
    }

}
