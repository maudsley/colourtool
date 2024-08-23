#ifndef FAVOURITEITEMWIDGET_H
#define FAVOURITEITEMWIDGET_H

#include <QFrame>
#include <QLabel>

class FavouriteItemWidget : public QFrame
{
    Q_OBJECT
public:
    explicit FavouriteItemWidget(const QColor& colour);

private:

    QPixmap drawTile() const;

    void setupCollapsedView();
    void setupExpandedView();

    void collapseView();
    void expandView();

    QString colourRgbString() const;

    QWidget* collapsedWidget_;
    QWidget* expandedWidget_;

    QColor colour_;

};

#endif // FAVOURITEITEMWIDGET_H
