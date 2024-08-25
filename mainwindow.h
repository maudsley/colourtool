#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basecolourwidget.h"
#include "favouriteswidget.h"
#include "colourgridwidget.h"
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

    void makeRandomColours();
    void showAboutInformation();

    Ui::MainWindow *ui;

    BaseColourWidget* baseColourWidget_;

    ColourGridWidget* colourGridWidget_;

    FavouritesWidget* favouritesWidget_;

    ColourWheelDisplay* colourWheelDisplay_;

};

#endif // MAINWINDOW_H
