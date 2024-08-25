#include "frameseperator.h"
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

FrameSeperator::FrameSeperator(const QString& label)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QFrame* leftFrame = new QFrame();
    leftFrame->setFrameShape(QFrame::HLine);
    layout->addWidget(leftFrame);

    if (!label.isEmpty())
    {
        QFrame* textLabel = new QLabel(label);
        layout->addWidget(textLabel);

        QFrame* rightFrame = new QFrame();
        rightFrame->setFrameShape(QFrame::HLine);
        layout->addWidget(rightFrame);
    }

    setEnabled(false); // Easy way to get alternative style
}
