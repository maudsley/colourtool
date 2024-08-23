#ifndef COLOURWHEEL_H
#define COLOURWHEEL_H

#include <QWidget>
#include "colourwheelindicators.h"
#include <optional>

class ColourWheel : public QWidget
{
    Q_OBJECT
public:
    explicit ColourWheel(QWidget *parent = nullptr);

    void setIndicators(const ColourWheelIndicators& indicators);

    ColourWheelIndicators indicators() const;

    void setActiveIndicatorColour(const QColor& colour);

    std::optional<QColor> activeIndicatorColour() const;

    QRect wheelRect() const;

    int wheelRectBuffer() const;

signals:

    void wheelColourChanged();

private:

    QImage drawWheelImage();

    QPoint pointFromColour(const QColor& colour) const;

    QColor colourFromWidgetPoint(const QPoint& point) const;

    QColor colourFromImagePoint(const QPoint& point) const;

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    QImage wheelImage_;

    ColourWheelIndicators indicators_;

    bool mouseDown_{ false };

};

#endif // COLOURWHEEL_H
