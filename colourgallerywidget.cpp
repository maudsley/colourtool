#include "colourgallerywidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

ColourGalleryWidget::ColourGalleryWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedHeight(100);
}

void ColourGalleryWidget::setGalleryIndicators(const ColourWheelIndicators& indicators)
{
    galleryIndicators_ = indicators;

    update();
}

ColourWheelIndicators ColourGalleryWidget::galleryIndicators() const
{
    return galleryIndicators_;
}

std::vector<QRect> ColourGalleryWidget::tileRects() const
{
    std::vector<QRect> tiles;

    std::vector<QColor> colours = galleryIndicators_.colours();

    int rectSize = 40;

    int rectSpacing = 10;

    int allRectsWidth = rectSize * colours.size() + rectSpacing * (colours.size() - 1);

    for (size_t i = 0; i < colours.size(); i++)
    {
        QRect tile(0, 0, rectSize, rectSize);

        tile.translate(i * (rectSize + rectSpacing), 0);

        tile.translate(rect().center() - QPoint(allRectsWidth, rectSize) / 2);

        tiles.push_back(tile);
    }

    return tiles;
}

void ColourGalleryWidget::changeTileSelection(const size_t index)
{
    galleryIndicators_.setSelectedIndicator(index);

    emit galleryIndicatorSelectionChanged();

    update();
}

void ColourGalleryWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragStartPosition_ = event->pos();

        // Check for tile selection change

        std::vector<QRect> tiles = tileRects();

        for (size_t i = 0; i < tiles.size(); i++)
        {
            if (tiles.at(i).contains(dragStartPosition_))
            {
                changeTileSelection(i);
                break;
            }
        }
    }
}

void ColourGalleryWidget::mouseMoveEvent(QMouseEvent *event)
{
    std::vector<QRect> tiles = tileRects();

    std::vector<QColor> colours = galleryIndicators_.colours();

    for (size_t i = 0; i < tiles.size(); i++)
    {
        if (tiles.at(i).contains(dragStartPosition_))
        {
            // Dragging from within a tile

            double dist = (event->pos() - dragStartPosition_).manhattanLength();
            if (dist >= QApplication::startDragDistance())
            {
                QDrag *drag = new QDrag(this);
                QMimeData *mimeData = new QMimeData;

                mimeData->setColorData(colours.at(i));

                drag->setMimeData(mimeData);

                QPixmap icon(32, 32);
                icon.fill(colours.at(i));
                drag->setPixmap(icon);

                drag->exec(Qt::CopyAction);
            }

            break;
        }
    }
}

void ColourGalleryWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    painter.setPen(Qt::gray);
    painter.drawLine(0, 0, width(), 0);

    std::vector<QColor> colours = galleryIndicators_.colours();

    std::optional<size_t> selectedColour = galleryIndicators_.selectedIndicator();

    std::vector<QRect> tiles = tileRects();

    for (size_t i = 0; i < tiles.size(); i++)
    {
        bool selected = false;

        if (selectedColour)
        {
            if (selectedColour.value() == i)
            {
                selected = true;
            }
        }

        QRect tile = tiles.at(i);

        // Draw tile border

        if (selected)
        {
            painter.fillRect(tile, Qt::white);
            painter.setPen(Qt::black);
            painter.drawRect(tile);
        }
        else
        {
            painter.fillRect(tile, Qt::white);
            painter.setPen(Qt::lightGray);
            painter.drawRect(tile);
        }

        // Draw colour tile interior

        tile.adjust(2, 2, -2, -2);

        QPoint startGradient(tile.center().x(), tile.top());
        QPoint stopGradient(tile.center().x(), tile.bottom());
        QLinearGradient sgrad(startGradient, stopGradient);
        sgrad.setColorAt(0.0, colours.at(i));
        sgrad.setColorAt(0.25, colours.at(i).lighter(125));
        sgrad.setColorAt(1.0, colours.at(i));
        painter.fillRect(tile, sgrad);

//        painter.fillRect(tile, colours.at(i));
        painter.setPen(colours.at(i).darker());
        painter.drawRect(tile);

        // Draw reflection

        QRect reflection = tile;
        reflection.translate(0, tile.height());
        reflection.setBottom(reflection.bottom() - reflection.height() / 2);

        QColor transparentColour = colours.at(i);
        transparentColour.setAlphaF(0.35);

        startGradient = QPoint(reflection.center().x(), reflection.top());
        stopGradient = QPoint(reflection.center().x(), reflection.bottom());

        QLinearGradient lgrad(startGradient, stopGradient);
        lgrad.setColorAt(0.0, transparentColour);
        lgrad.setColorAt(1.0, QColor(0,0,0,0));
        painter.fillRect(reflection, lgrad);
    }

}
