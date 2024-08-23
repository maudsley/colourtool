#ifndef FAVOURITESWIDGET_H
#define FAVOURITESWIDGET_H

#include <QDockWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class FavouritesWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit FavouritesWidget(QWidget *parent = nullptr);

signals:

private:

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *event) override;

    QScrollArea* scrollArea_;
    QWidget* scrollAreaWidget_;
    QVBoxLayout* layout_;

};

#endif // FAVOURITESWIDGET_H
