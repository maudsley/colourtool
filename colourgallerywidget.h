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

private:

    void paintEvent(QPaintEvent *event) override;

    ColourWheelIndicators galleryIndicators_;

};

#endif // COLOURGALLERYWIDGET_H
