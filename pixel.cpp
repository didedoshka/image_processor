#include "pixel.hpp"
#include <cmath>
#include <cstdint>

Pixel::Pixel()
    : red_(static_cast<Pixel::Channel>(0)),
      green_(static_cast<Pixel::Channel>(0)),
      blue_(static_cast<Pixel::Channel>(0)) {
}

Pixel::Pixel(Pixel::Channel red, Pixel::Channel green, Pixel::Channel blue) {
    SetRed(red);
    SetGreen(green);
    SetBlue(blue);
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue)
    : red_(static_cast<Pixel::Channel>(red) / UINT8_MAX),
      green_(static_cast<Pixel::Channel>(green) / UINT8_MAX),
      blue_(static_cast<Pixel::Channel>(blue) / UINT8_MAX) {
}
void Pixel::SetRed(Pixel::Channel red) {
    red_ = std::clamp(red, Channel{0.0}, Channel{1.0});
}

void Pixel::SetGreen(Pixel::Channel green) {
    green_ = std::clamp(green, Channel{0.0}, Channel{1.0});
}

void Pixel::SetBlue(Pixel::Channel blue) {
    blue_ = std::clamp(blue, Channel{0.0}, Channel{1.0});
}

Pixel::Channel Pixel::GetRed() const {
    return red_;
}

Pixel::Channel Pixel::GetGreen() const {
    return green_;
}

Pixel::Channel Pixel::GetBlue() const {
    return blue_;
}

uint8_t Pixel::ChannelToUInt8T(Pixel::Channel brightness) {
    return static_cast<uint8_t>(std::round(brightness * UINT8_MAX));
}

std::ostream& operator<<(std::ostream& os, const Pixel& pixel) {
    return os << pixel.red_ << ' ' << pixel.green_ << ' ' << pixel.blue_;
}
