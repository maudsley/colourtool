#ifndef HSLCOLOURSAMPLER_H
#define HSLCOLOURSAMPLER_H

#include "coloursamplerdelegate.h"

class HslColourSampler : public ColourSamplerDelegate
{
public:
    HslColourSampler();

    ~HslColourSampler() override;

    enum Channel {ChannelNone, ChannelHue, ChannelSaturation, ChannelLightness};

    void setChannel(const Channel channel);

    Channel getChannel() const;

    void setColour(const QColor& colour);

    QColor getColor() const;

    QColor getColourAtPosition(const double position) const override;

    double getPosition() const override;

    int getMaxValue() const override;

private:

    Channel channel_{ ChannelNone };

    QColor colour_{ Qt::black };
};

#endif // HSLCOLOURSAMPLER_H
