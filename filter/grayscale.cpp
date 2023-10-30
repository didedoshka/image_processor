#include "grayscale.hpp"

const Pixel Grayscale::WEIGHTS = Pixel(0.299f, 0.587f, 0.114f);

Grayscale::Grayscale() {
    change_pixel_ = [](const Pixel& pixel) {
        Pixel::Channel brightness = WEIGHTS.GetRed() * pixel.GetRed() + WEIGHTS.GetGreen() * pixel.GetGreen() +
                                    WEIGHTS.GetBlue() * pixel.GetBlue();
        return Pixel(brightness, brightness, brightness);
    };
}
