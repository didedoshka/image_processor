#include "change_pixels.hpp"

ChangePixels::ChangePixels(std::function<Pixel(const Pixel&)> change_pixel) : change_pixel_(change_pixel) {
}

Image ChangePixels::operator()(const Image& image) {
    Image result(image.GetWidth(), image.GetHeight());
    for (Image::SizeType row = 0; row < image.GetHeight(); ++row) {
        for (Image::SizeType column = 0; column < image.GetWidth(); ++column) {
            result.At(row, column) = change_pixel_(image.At(row, column));
        }
    }
    return result;
}
