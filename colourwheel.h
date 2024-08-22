#ifndef COLOURWHEEL_H
#define COLOURWHEEL_H

#include <QWidget>

class ColourWheel : public QWidget
{
    Q_OBJECT
public:
    explicit ColourWheel(QWidget *parent = nullptr);

    void setIndicatorColour(const QColor& indicatorColour);

    QColor indicatorColour() const;

    QRect wheelRect() const;

    int wheelRectBuffer() const;

signals:

    void wheelColourChanged();

private:

    QPoint indicatorColourPos() const;

    QColor colourFromPoint(const QPoint& point) const;

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    QColor indicatorColour_;

    bool mouseDown_{ false };

};

#endif // COLOURWHEEL_H
