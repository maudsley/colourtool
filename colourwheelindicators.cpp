#include "colourwheelindicators.h"

ColourWheelIndicators::ColourWheelIndicators()
{

}

std::vector<QColor> ColourWheelIndicators::colours() const
{
    return colours_;
}

void ColourWheelIndicators::setColours(const std::vector<QColor>& colours)
{
    colours_ = colours;
}

std::optional<size_t> ColourWheelIndicators::selectedIndicator() const
{
    return selectedIndicator_;
}

void ColourWheelIndicators::setSelectedIndicator(const std::optional<size_t>& selectedIndicator)
{
    selectedIndicator_ = selectedIndicator;
}

void ColourWheelIndicators::setActiveIndicatorColour(const QColor& colour)
{
    if (selectedIndicator_)
    {
        // Update the colour of the selected wheel indicator

        colours_[selectedIndicator_.value()] = colour;
    }
}

std::optional<QColor> ColourWheelIndicators::activeIndicatorColour() const
{
    std::optional<QColor> result;

    for (size_t i = 0; i < colours_.size(); i++)
    {
        if (selectedIndicator_)
        {
            if (selectedIndicator_.value() == i)
            {
                result = colours_.at(i);

                break;
            }
        }
    }

    return result;
}
