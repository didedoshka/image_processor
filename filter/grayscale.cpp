#include "grayscale.hpp"

Grayscale::Grayscale() {
    change_pixel_ = [](const Pixel& pixel) {
        Pixel::Channel brightness = static_cast<Pixel::Channel>(0.299) * pixel.GetRed() +
                                    static_cast<Pixel::Channel>(0.587) * pixel.GetGreen() +
                                    static_cast<Pixel::Channel>(0.114) * pixel.GetBlue();
        return Pixel(brightness, brightness, brightness);
    };
}
