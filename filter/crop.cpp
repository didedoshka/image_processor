#include "crop.hpp"

Crop::Crop(Image::SizeType width, Image::SizeType height) {
    width_ = std::max(static_cast<Image::SizeType>(0), width);
    height_ = std::max(static_cast<Image::SizeType>(0), height);
}

Image Crop::operator()(const Image& image) {
    Image result(std::min(width_, image.GetWidth()), std::min(height_, image.GetHeight()));
    for (Image::SizeType row = 0; row < result.GetHeight(); ++row) {
        for (Image::SizeType column = 0; column < result.GetWidth(); ++column) {
            result.At(row, column) = image.At(row, column);
        }
    }
    return result;
}
