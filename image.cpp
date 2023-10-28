#include "image.hpp"

Image::Image(Image::SizeType width, Image::SizeType height) : width_(width), height_(height), pixels_(width_ * height_) {
}

const Image::SizeType Image::GetWidth() const {
    return width_;
}
const Image::SizeType Image::GetHeight() const {
    return height_;
}

const PixelDouble& Image::At(Image::SizeType row, Image::SizeType column) const {
    return pixels_[row * width_ + column];
}

PixelDouble& Image::At(Image::SizeType row, Image::SizeType column) {
    return pixels_[row * width_ + column];
}
