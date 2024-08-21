#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colourslider.h"
#include "colourrectanglewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSliderColours(const QColor& colour);

    void handleRedSliderChanged();
    void handleGreenSliderChanged();
    void handleBlueSliderChanged();

private:

    Ui::MainWindow *ui;

    ColourRectangleWidget* colourRectangle_;
    ColourSlider* redSlider_;
    ColourSlider* greenSlider_;
    ColourSlider* blueSlider_;

};
#endif // MAINWINDOW_H
