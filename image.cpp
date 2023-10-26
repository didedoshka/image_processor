#include "image.hpp"

Image::Image(size_t width, size_t height) : width_(width), height_(height), pixels_(width_ * height_) {
}

const size_t Image::GetWidth() const {
    return width_;
}
const size_t Image::GetHeight() const {
    return height_;
}

const PixelDouble& Image::At(size_t x, size_t y) const {
    return pixels_[y * width_ + x];
}

PixelDouble& Image::At(size_t x, size_t y) {
    return pixels_[y * width_ + x];
}
