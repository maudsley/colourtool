#ifndef COLOURGRID_H
#define COLOURGRID_H

#include <QWidget>

class ColourGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ColourGrid(QWidget *parent = nullptr);

    QColor colour() const;

    void setColour(const QColor& colour);

signals:

    void onColourSelected(const QColor& colour);

private:

    QSize getTileSize() const;

    QColor pointToColour(const QPoint& point) const;

    void paintEvent(QPaintEvent*) override;

    void mousePressEvent(QMouseEvent *event) override;

    QColor colour_;

};

#endif // COLOURGRID_H
