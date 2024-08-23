#ifndef COLOURRECTANGLEWIDGET_H
#define COLOURRECTANGLEWIDGET_H

#include <QWidget>
#include <QColor>

class ColourRectangleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColourRectangleWidget(QWidget *parent = nullptr);

    void setColour(const QColor& colour);

    QColor colour() const;

    void paintEvent(QPaintEvent *event) override;

signals:

private:

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    QColor colour_;

    QPoint dragStartPosition_;

};

#endif // COLOURRECTANGLEWIDGET_H
