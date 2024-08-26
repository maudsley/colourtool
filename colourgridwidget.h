#ifndef COLOURGRIDWIDGET_H
#define COLOURGRIDWIDGET_H

#include <QDockWidget>
#include "colourgrid.h"

class ColourGridWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ColourGridWidget(QWidget *parent = nullptr);

    QColor colour() const;

    void setColour(const QColor& colour);

signals:

    void onColourSelected(const QColor& colour);

private:

    ColourGrid* colourGrid_;

};

#endif // COLOURGRIDWIDGET_H
