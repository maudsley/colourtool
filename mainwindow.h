#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basecolourwidget.h"
#include "colourwheeldisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleBaseColourChanged();

    void handleWheelColourChanged();

private:

    Ui::MainWindow *ui;

    BaseColourWidget* baseColourWidget_;
    ColourWheelDisplay* colourWheelDisplay_;

};

#endif // MAINWINDOW_H
