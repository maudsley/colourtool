#include "favouriteswidget.h"
#include "frameseperator.h"
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QToolBar>
#include <QTableWidget>
#include <QHeaderView>
#include <QApplication>
#include <QClipboard>

FavouritesWidget::FavouritesWidget(QWidget *parent)
    : QDockWidget{parent}
{
    setWindowTitle("Favourite Colours");
    setFeatures(QDockWidget::DockWidgetFloatable);
    setMinimumWidth(220);
    setAcceptDrops(true);

    QWidget* centralWidget = new QWidget();
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    infoMessage_ = new FavouritesInformation();
    layout->addWidget(infoMessage_);

    table_ = new QTableWidget();
    layout->addWidget(table_);

    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->horizontalHeader()->setStretchLastSection(true);
    table_->horizontalHeader()->hide();
    table_->verticalHeader()->hide();
    table_->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
    table_->setColumnCount(1);
    table_->setFocusPolicy(Qt::NoFocus);

    QColor windowColour = palette().window().color();
    table_->setStyleSheet(QString("QTableView { background-color: %1; }").arg(windowColour.name()));

    QToolBar* bottomBar = new QToolBar();
    bottomBar->setIconSize(QSize(16, 16));
    layout->addWidget(bottomBar);
    QAction* copyAction = bottomBar->addAction(QIcon(":/icons/copy.png"), "Copy");
    connect(copyAction, &QAction::triggered, this, &FavouritesWidget::copySelected);
    QAction* pasteAction = bottomBar->addAction(QIcon(":/icons/paste.png"), "Paste");
    connect(pasteAction, &QAction::triggered, this, &FavouritesWidget::pasteItem);
    QAction* deleteAction = bottomBar->addAction(QIcon(":/icons/delete.png"), "Delete");
    connect(deleteAction, &QAction::triggered, this, &FavouritesWidget::deleteSelected);

    updateTableDisplay();
}

void FavouritesWidget::updateTableDisplay()
{
    if (table_->rowCount() == 0)
    {
        infoMessage_->show();
        table_->hide();
    }
    else
    {
        infoMessage_->hide();
        table_->show();
    }
}

FavouriteItemWidget* FavouritesWidget::addFavourite(const QColor& colour)
{
    FavouriteItemWidget* item = new FavouriteItemWidget(colour);
    connect(item, &FavouriteItemWidget::onItemExpand, this, &FavouritesWidget::saveSelection);
    connect(item, &FavouriteItemWidget::onItemExpanded, this, &FavouritesWidget::restoreSelectionAndResize);
    connect(item, &FavouriteItemWidget::onItemCollapse, this, &FavouritesWidget::saveSelection);
    connect(item, &FavouriteItemWidget::onItemCollapsed, this, &FavouritesWidget::restoreSelectionAndResize);

    table_->insertRow(0);
    table_->setCellWidget(0, 0, item);
    table_->resizeRowsToContents();

    updateTableDisplay();

    return item;
}

void FavouritesWidget::deleteSelected()
{
    QModelIndexList selectedItems = table_->selectionModel()->selectedRows();

    for (QModelIndex index : selectedItems)
    {
        table_->removeRow(index.row());
    }

    updateTableDisplay();
}

void FavouritesWidget::copySelected()
{
    QModelIndexList selectedItems = table_->selectionModel()->selectedRows();

    if (selectedItems.size() == 1)
    {
        // Exactly one item is selected

        QModelIndex modelIndex = selectedItems.at(0);

        QWidget* widget = table_->cellWidget(modelIndex.row(), modelIndex.column());

        // Find the colour

        FavouriteItemWidget* favouriteItem = dynamic_cast<FavouriteItemWidget*>(widget);

        QColor colour = favouriteItem->colour();

        // Copy to clipboard

        QClipboard *clipboard = QApplication::clipboard();

        clipboard->setText(colour.name());
    }
}

void FavouritesWidget::pasteItem()
{
    QClipboard *clipboard = QApplication::clipboard();

    QColor colour(clipboard->text());

    addFavourite(colour);
}

void FavouritesWidget::saveSelection()
{
    tableSavedSelection_ = table_->selectionModel()->selectedRows();
}

void FavouritesWidget::restoreSelectionAndResize()
{
    table_->clearSelection();

    for (const QModelIndex& index : tableSavedSelection_)
    {
        table_->selectionModel()->select(index, QItemSelectionModel::Select);
    }

    table_->resizeRowsToContents();
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

        addFavourite(colour);

        event->acceptProposedAction();
    }
}
