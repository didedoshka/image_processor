#include "grayscale.hpp"

Grayscale::Grayscale() {
    change_pixel_ = [](const PixelDouble& pixel) {
        double brightness = 0.299 * pixel.GetRed() + 0.587 * pixel.GetGreen() + 0.114 * pixel.GetBlue();
        return PixelDouble(brightness, brightness, brightness);
    };
}
