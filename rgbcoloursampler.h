#ifndef RGBCOLOURSAMPLER_H
#define RGBCOLOURSAMPLER_H

#include "coloursamplerdelegate.h"

class RgbColourSampler : public ColourSamplerDelegate
{
public:
    RgbColourSampler();

    ~RgbColourSampler() override;

    enum Channel {ChannelNone, ChannelRed, ChannelGreen, ChannelBlue};

    void setChannel(const Channel channel);

    Channel getChannel() const;

    void setColour(const QColor& colour);

    QColor getColor() const;

    QColor getColourAtPosition(const double position) const override;

    double getPosition() const override;

private:

    Channel channel_{ ChannelNone };

    QColor colour_{ Qt::black };

};

#endif // RGBCOLOURSAMPLER_H
