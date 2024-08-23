#ifndef COLOURGALLERYWIDGET_H
#define COLOURGALLERYWIDGET_H

#include <QWidget>
#include "colourwheelindicators.h"

class ColourGalleryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColourGalleryWidget(QWidget *parent = nullptr);

    void setGalleryIndicators(const ColourWheelIndicators& indicators);

    ColourWheelIndicators galleryIndicators() const;

signals:

    void galleryIndicatorSelectionChanged();

private:

    std::vector<QRect> tileRects() const;

    void changeTileSelection(const size_t index);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    ColourWheelIndicators galleryIndicators_;

    QPoint dragStartPosition_;

};

#endif // COLOURGALLERYWIDGET_H
