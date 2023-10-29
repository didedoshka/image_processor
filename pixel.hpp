#pragma once

#include <cstdint>
#include <ostream>

class Pixel {
public:
    using Channel = float;
    Pixel();
    Pixel(Channel red, Channel green, Channel blue);
    Pixel(uint8_t red, uint8_t green, uint8_t blue);

    void SetRed(Channel red);
    void SetGreen(Channel green);
    void SetBlue(Channel blue);

    Channel GetRed() const;
    Channel GetGreen() const;
    Channel GetBlue() const;

    static uint8_t ChannelToUInt8T(Channel brightness);

    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);

private:
    Channel red_;
    Channel green_;
    Channel blue_;
};
