#ifndef COLOURSLIDER_H
#define COLOURSLIDER_H

#include <QWidget>
#include "coloursliderbar.h"
#include "coloursliderindicator.h"
#include "coloursamplerdelegate.h"
#include <QLineEdit>
#include <QPoint>
#include <optional>
#include <memory>

class ColourSlider : public QWidget
{
    Q_OBJECT
public:
    explicit ColourSlider(const QString& label);

    double sliderValue();

    void setSliderValue(const double value);

    QColor sliderColour() const;

    void setColourSamplerDelegate(const std::shared_ptr<ColourSamplerDelegate>& colourSamplerDelegate);

signals:

    void indicatorMoved();

private:

    void setSliderPosFromPoint(const QPoint& point);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void colourSliderTextChanged();

    ColourSliderBar* bar_;

    ColourSliderIndicator* indicator_;

    QLineEdit* edit_;

    bool mouseDown_{ false };

};

#endif // COLOURSLIDER_H
