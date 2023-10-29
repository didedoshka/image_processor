#include "negative.hpp"

Negative::Negative() {
    change_pixel_ = [](const PixelDouble& pixel) {
        return PixelDouble(1.0 - pixel.GetRed(), 1.0 - pixel.GetGreen(), 1.0 - pixel.GetBlue());
    };
}
