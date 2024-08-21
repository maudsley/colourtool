#ifndef COLOURSLIDERINDICATOR_H
#define COLOURSLIDERINDICATOR_H

#include <QWidget>

class ColourSliderIndicator : public QWidget
{
    Q_OBJECT
public:

    explicit ColourSliderIndicator(QWidget *parent = nullptr);

    QRect indicatorRect() const;

    QRect indicatorGeometry() const;

    double indicatorPosition() const;

    void setIndicatorPosition(const double position);

    void paintEvent(QPaintEvent *event) override;

signals:

private:

    double position_{ 0.5 };

};

#endif // COLOURSLIDERINDICATOR_H
