#include "hslcoloursampler.h"

HslColourSampler::HslColourSampler()
{

}

HslColourSampler::~HslColourSampler()
{

}

void HslColourSampler::setChannel(const Channel channel)
{
    channel_ = channel;
}

HslColourSampler::Channel HslColourSampler::getChannel() const
{
    return channel_;
}

void HslColourSampler::setColour(const QColor& colour)
{
    colour_ = colour;
}

QColor HslColourSampler::getColor() const
{
    return colour_;
}

QColor HslColourSampler::getColourAtPosition(const double position) const
{
    float h;
    float s;
    float l;

    colour_.getHslF(&h, &s, &l);

    switch (channel_)
    {
    case ChannelHue:
        h = position;
        break;
    case ChannelSaturation:
        s = position;
        break;
    case ChannelLightness:
        l = position;
        break;
    default:
        throw std::runtime_error("Unknown colour HSL channel");
    }

    QColor colour;
    colour.setHslF(h, s, l);

    return colour;
}

double HslColourSampler::getPosition() const
{
    float h;
    float s;
    float l;

    colour_.getHslF(&h, &s, &l);

    double pos = 0;

    switch (channel_)
    {
    case ChannelHue:
        pos = h;
        break;
    case ChannelSaturation:
        pos = s;
        break;
    case ChannelLightness:
        pos = l;
        break;
    default:
        throw std::runtime_error("Unknown colour HSL channel");
    }

    return pos;
}

int HslColourSampler::getMaxValue() const
{
    // See https://doc.qt.io/qt-6/qcolor.html#the-hsv-color-model

    int maxValue = 0;

    switch (channel_)
    {
    case ChannelHue:
        maxValue = 359; // Note: range is [0, 359]
        break;
    case ChannelSaturation:
        maxValue = 255;
        break;
    case ChannelLightness:
        maxValue = 255;
        break;
    default:
        throw std::runtime_error("Unknown colour HSL channel");
    }

    return maxValue;
}
