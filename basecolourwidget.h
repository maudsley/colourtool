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

signals:

    void baseColourChanged();

private:

    void handleRedSliderChanged();
    void handleGreenSliderChanged();
    void handleBlueSliderChanged();

    void handleHueSliderChanged();
    void handleSaturationSliderChanged();
    void handleLightnessSliderChanged();

    void buttonSaturationIncrement();
    void buttonSaturationDecrement();
    void buttonLightnessIncrement();
    void buttonLightnessDecrement();

    void handleHexEditChanged();

    void handleCopyColour();
    void handlePasteColour();

    ColourRectangleWidget* colourRectangle_;

    ColourSlider* redSlider_;
    ColourSlider* greenSlider_;
    ColourSlider* blueSlider_;

    ColourSlider* hueSlider_;
    ColourSlider* saturationSlider_;
    ColourSlider* lightnessSlider_;

    QLineEdit* hexEdit_;

};

#endif // BASECOLOURWIDGET_H
