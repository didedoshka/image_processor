#pragma once

#include <cstdint>
#include <ostream>

struct PixelDouble {
    double red;
    double green;
    double blue;

    PixelDouble();
    PixelDouble(double red, double green, double blue);
    PixelDouble(uint8_t red, uint8_t green, uint8_t blue);

    friend std::ostream& operator<<(std::ostream& os, const PixelDouble& pixel);
};
