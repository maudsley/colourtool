#ifndef COLOURWHEELDISPLAY_H
#define COLOURWHEELDISPLAY_H

#include <QWidget>
#include "colourwheel.h"
#include "colourgallerywidget.h"
#include "colourwheelindicators.h"

class ColourWheelDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ColourWheelDisplay(QWidget *parent = nullptr);

    void setDisplayIndicators(const ColourWheelIndicators& indicators);

    ColourWheelIndicators displayIndicators() const;

    void setActiveDisplayIndicatorColour(const QColor& colour);

    std::optional<QColor> activeDisplayIndicatorColour() const;

signals:

    void wheelColourDisplayChanged();

private:

    void wheelDisplayChanged();

    ColourWheel* colourWheel_;

    ColourGalleryWidget* colourGalleryWidget_;

};

#endif // COLOURWHEELDISPLAY_H
