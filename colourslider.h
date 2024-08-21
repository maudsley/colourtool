#ifndef COLOURSLIDER_H
#define COLOURSLIDER_H

#include <QWidget>
#include "coloursliderbar.h"
#include "coloursliderindicator.h"
#include "coloursamplerdelegate.h"
#include <QPoint>
#include <optional>
#include <memory>

class ColourSlider : public QWidget
{
    Q_OBJECT
public:
    explicit ColourSlider(QWidget *parent = nullptr);

    QColor sliderColour() const;

    void setColourSamplerDelegate(const std::shared_ptr<ColourSamplerDelegate>& colourSamplerDelegate);

    std::shared_ptr<ColourSamplerDelegate> colourBarSamplerDelegate() const;

signals:

    void indicatorMoved();

private:

    void setSliderPosFromPoint(const QPoint& point);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    ColourSliderBar* bar_;

    ColourSliderIndicator* indicator_;

    bool mouseDown_{ false };

};

#endif // COLOURSLIDER_H
