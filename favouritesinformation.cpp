#include "favouritesinformation.h"
#include <QVBoxLayout>
#include <QLabel>

FavouritesInformation::FavouritesInformation(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignHCenter);

    QLabel* label = new QLabel("Drag & drop colours\nhere to add them\nto favourites");
    label->setAlignment(Qt::AlignHCenter);
    label->setWordWrap(true);

    layout->addWidget(label);
}
