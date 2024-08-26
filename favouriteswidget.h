#ifndef FAVOURITESWIDGET_H
#define FAVOURITESWIDGET_H

#include <QDockWidget>
#include "favouriteitemwidget.h"
#include "favouritesinformation.h"
#include <QTableWidget>

class FavouritesWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit FavouritesWidget(QWidget *parent = nullptr);

private:

    void updateTableDisplay();

    FavouriteItemWidget* addFavourite(const QColor& colour);

    void deleteSelected();

    void copySelected();

    void pasteItem();

    void saveSelection();

    void restoreSelectionAndResize();

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *event) override;

    FavouritesInformation* infoMessage_;

    QTableWidget* table_;

    QModelIndexList tableSavedSelection_;

};

#endif // FAVOURITESWIDGET_H
