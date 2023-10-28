#include "pixel.hpp"
#include <cmath>
#include <cstdint>

PixelDouble::PixelDouble() : red(0.0), green(0.0), blue(0.0) {
}

PixelDouble::PixelDouble(double red, double green, double blue) : red(red), green(green), blue(blue) {
}

PixelDouble::PixelDouble(uint8_t red, uint8_t green, uint8_t blue)
    : red(static_cast<double>(red) / UINT8_MAX),
      green(static_cast<double>(green) / UINT8_MAX),
      blue(static_cast<double>(blue) / UINT8_MAX) {
}

uint8_t PixelDouble::DoubleToUInt8T(double brightness) {
    return static_cast<uint8_t>(std::round(std::max(std::min(brightness, 1.0), 0.0) * UINT8_MAX));
}

std::ostream& operator<<(std::ostream& os, const PixelDouble& pixel) {
    return os << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}
