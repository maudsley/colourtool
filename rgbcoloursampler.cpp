#include "rgbcoloursampler.h"

RgbColourSampler::RgbColourSampler()
{

}

RgbColourSampler::~RgbColourSampler()
{

}

void RgbColourSampler::setChannel(const Channel channel)
{
    channel_ = channel;
}

RgbColourSampler::Channel RgbColourSampler::getChannel() const
{
    return channel_;
}

void RgbColourSampler::setColour(const QColor& colour)
{
    colour_ = colour;
}

QColor RgbColourSampler::getColor() const
{
    return colour_;
}

QColor RgbColourSampler::getColourAtPosition(const double position) const
{
    QColor colour = colour_;

    switch (channel_)
    {
    case ChannelRed:
        colour.setRedF(position);
        break;
    case ChannelGreen:
        colour.setGreenF(position);
        break;
    case ChannelBlue:
        colour.setBlueF(position);
        break;
    default:
        throw std::runtime_error("Unknown colour RGB channel");
    }

    return colour;
}

double RgbColourSampler::getPosition() const
{
    double pos = 0;

    switch (channel_)
    {
    case ChannelRed:
        pos = colour_.redF();
        break;
    case ChannelGreen:
        pos = colour_.greenF();
        break;
    case ChannelBlue:
        pos = colour_.blueF();
        break;
    default:
        throw std::runtime_error("Unknown colour RGB channel");
    }

    return pos;
}

int RgbColourSampler::getMaxValue() const
{
    return 255;
}
