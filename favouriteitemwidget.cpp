#include "favouriteitemwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

FavouriteItemWidget::FavouriteItemWidget(const QColor& colour) : colour_(colour)
{
    setFrameStyle(QFrame::Panel | QFrame::Raised);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(3, 3, 3, 3);
    setLayout(vlayout);

    collapsedWidget_ = new QWidget();
    vlayout->addWidget(collapsedWidget_);

    expandedWidget_ = new QWidget();
    vlayout->addWidget(expandedWidget_);

    setupCollapsedView();
    setupExpandedView();

    collapseView(); // Initially collapsed
}

QPixmap FavouriteItemWidget::drawTile() const
{
    QPixmap pixmap(32, 32);

    QPainter painter(&pixmap);

    QRect tile(0, 0, pixmap.width(), pixmap.height());

    // Draw tile border

    painter.fillRect(tile, Qt::gray);
    painter.setPen(Qt::gray);
    painter.drawRect(tile);

    // Draw colour tile interior

    tile.adjust(1, 1, -1, -1);

    painter.fillRect(tile, colour_);
    painter.setPen(Qt::black);
    painter.drawRect(tile);

    return pixmap;
}

void FavouriteItemWidget::setupCollapsedView()
{
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);
    collapsedWidget_->setLayout(vlayout);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addLayout(hlayout);

    QLabel* tile = new QLabel();
    tile->setPixmap(drawTile());
    hlayout->addWidget(tile);

    QLabel* name = new QLabel();
    name->setText(colour_.name());
    name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    hlayout->addWidget(name);

    hlayout->addStretch();

    QPixmap arrow(":/icons/right.png");
    QPushButton* button = new QPushButton();
    button->setFixedSize(16, 16);
    connect(button, &QPushButton::clicked, this, &FavouriteItemWidget::expandView);
    button->setIcon(arrow);
    hlayout->addWidget(button);
}

void FavouriteItemWidget::setupExpandedView()
{
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);
    expandedWidget_->setLayout(vlayout);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addLayout(hlayout);

    QLabel* tile = new QLabel();
    tile->setPixmap(drawTile());
    hlayout->addWidget(tile);

    QLabel* name = new QLabel();
    name->setText(colour_.name());
    name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    hlayout->addWidget(name);

    hlayout->addStretch();

    QPixmap arrow(":/icons/down.png");
    QPushButton* button = new QPushButton();
    button->setFixedSize(16, 16);
    connect(button, &QPushButton::clicked, this, &FavouriteItemWidget::collapseView);
    button->setIcon(arrow);
    hlayout->addWidget(button);

    QWidget* detailsWidget = new QWidget();
    detailsWidget->setStyleSheet("background-color:white;");
    vlayout->addWidget(detailsWidget);
    QVBoxLayout* details = new QVBoxLayout(detailsWidget);
    details->setSpacing(0);
    details->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* r1layout = new QHBoxLayout();
    details->addLayout(r1layout);
    r1layout->addWidget(new QLabel("Colour Values:"));
    r1layout->addStretch(1);

    QHBoxLayout* r2layout = new QHBoxLayout();
    details->addLayout(r2layout);
    r2layout->addWidget(new QLabel("RGB: "));
    r2layout->addWidget(new QLabel(colourRgbString()));
    r2layout->addStretch(1);

    QHBoxLayout* r3layout = new QHBoxLayout();
    details->addLayout(r3layout);
    r3layout->addWidget(new QLabel("Hex: "));
    r3layout->addWidget(new QLabel(colour_.name()));
    r3layout->addStretch(1);
}

void FavouriteItemWidget::collapseView()
{
    collapsedWidget_->show();
    expandedWidget_->hide();
}

void FavouriteItemWidget::expandView()
{
    collapsedWidget_->hide();
    expandedWidget_->show();
}

QString FavouriteItemWidget::colourRgbString() const
{
    QString result;
    result += QString::number(colour_.red()) + ",";
    result += QString::number(colour_.green()) + ",";
    result += QString::number(colour_.blue());
    return result;
}
