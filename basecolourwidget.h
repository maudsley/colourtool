#ifndef BASECOLOURWIDGET_H
#define BASECOLOURWIDGET_H

#include <QDockWidget>
#include "colourslider.h"
#include "colourrectanglewidget.h"

class BaseColourWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit BaseColourWidget(QWidget *parent = nullptr);

    QColor baseColour() const;

    void setSliderColours(const QColor& colour);

    void handleRedSliderChanged();
    void handleGreenSliderChanged();
    void handleBlueSliderChanged();

signals:

    void baseColourChanged();

private:

    ColourRectangleWidget* colourRectangle_;
    ColourSlider* redSlider_;
    ColourSlider* greenSlider_;
    ColourSlider* blueSlider_;

};

#endif // BASECOLOURWIDGET_H
