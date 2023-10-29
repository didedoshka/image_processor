#include "filter/crop.hpp"

Crop::Crop(Image::SizeType width, Image::SizeType height) {
    width_ = std::max(static_cast<Image::SizeType>(0), width);
    height_ = std::max(static_cast<Image::SizeType>(0), height);
}

Image Crop::operator()(const Image& image) {
    Image result(width_, height_);
    for (Image::SizeType row = 0; row < height_; ++row) {
        for (Image::SizeType column = 0; column < width_; ++column) {
            result.At(row, column) = image.At(row, column);
        }
    }
    return result;
}
