#include "pixel.hpp"
#include <cmath>
#include <cstdint>

PixelDouble::PixelDouble() : red_(0.0), green_(0.0), blue_(0.0) {
}

PixelDouble::PixelDouble(double red, double green, double blue) {
    SetRed(red);
    SetGreen(green);
    SetBlue(blue);
}

PixelDouble::PixelDouble(uint8_t red, uint8_t green, uint8_t blue)
    : red_(static_cast<double>(red) / UINT8_MAX),
      green_(static_cast<double>(green) / UINT8_MAX),
      blue_(static_cast<double>(blue) / UINT8_MAX) {
}
void PixelDouble::SetRed(double red) {
    red_ = std::min(1.0, std::max(0.0, red));
}

void PixelDouble::SetGreen(double green) {
    green_ = std::min(1.0, std::max(0.0, green));
}

void PixelDouble::SetBlue(double blue) {
    blue_ = std::min(1.0, std::max(0.0, blue));
}

double PixelDouble::GetRed() const {
    return red_;
}

double PixelDouble::GetGreen() const {
    return green_;
}

double PixelDouble::GetBlue() const {
    return blue_;
}

uint8_t PixelDouble::DoubleToUInt8T(double brightness) {
    return static_cast<uint8_t>(std::round(std::max(std::min(brightness, 1.0), 0.0) * UINT8_MAX));
}

std::ostream& operator<<(std::ostream& os, const PixelDouble& pixel) {
    return os << pixel.red_ << ' ' << pixel.green_ << ' ' << pixel.blue_;
}
