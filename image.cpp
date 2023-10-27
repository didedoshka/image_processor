#include "image.hpp"

Image::Image(uint32_t width, uint32_t height) : width_(width), height_(height), pixels_(width_ * height_) {
}

const uint32_t Image::GetWidth() const {
    return width_;
}
const uint32_t Image::GetHeight() const {
    return height_;
}

const PixelDouble& Image::At(uint32_t row, uint32_t column) const {
    return pixels_[row * width_ + column];
}

PixelDouble& Image::At(uint32_t row, uint32_t column) {
    return pixels_[row * width_ + column];
}
