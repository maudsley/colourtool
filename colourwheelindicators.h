#ifndef COLOURWHEELINDICATORS_H
#define COLOURWHEELINDICATORS_H

#include <QColor>
#include <optional>

class ColourWheelIndicators
{
public:

    ColourWheelIndicators();

    std::vector<QColor> colours() const;

    void setColours(const std::vector<QColor>& colours);

    std::optional<size_t> selectedIndicator() const;

    void setSelectedIndicator(const std::optional<size_t>& selectedIndicator);

    void setActiveIndicatorColour(const QColor& colour);

    std::optional<QColor> activeIndicatorColour() const;

private:

    std::vector<QColor> colours_;

    std::optional<size_t> selectedIndicator_;

};

#endif // COLOURWHEELINDICATORS_H
