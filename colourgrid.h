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

private:

    void paintEvent(QPaintEvent*);

    QColor colour_;

};

#endif // COLOURGRID_H
