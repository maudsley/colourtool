#ifndef COLOURSAMPLERDELEGATE_H
#define COLOURSAMPLERDELEGATE_H

#include <QColor>

class ColourSamplerDelegate
{
public:
    ColourSamplerDelegate();

    virtual ~ColourSamplerDelegate() = 0;

    virtual QColor getColourAtPosition(const double position) const = 0;

    virtual double getPosition() const = 0;

};

#endif // COLOURSAMPLERDELEGATE_H
