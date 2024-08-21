#ifndef COLOURSLIDERBAR_H
#define COLOURSLIDERBAR_H

#include <QWidget>
#include "coloursamplerdelegate.h"
#include <memory>

class ColourSliderBar : public QWidget
{
    Q_OBJECT
public:
    explicit ColourSliderBar(QWidget *parent = nullptr);

    void setColourBarSamplerDelegate(const std::shared_ptr<ColourSamplerDelegate>& colourSamplerDelegate);

    std::shared_ptr<ColourSamplerDelegate> colourBarSamplerDelegate() const;

    QRect sliderRect() const;

    QRect sliderGeometry() const;

    void paintEvent(QPaintEvent *event) override;

signals:

private:

    std::shared_ptr<ColourSamplerDelegate> colourSamplerDelegate_;

};

#endif // COLOURSLIDERBAR_H
