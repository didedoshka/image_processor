#pragma once

#include <vector>
#include "pixel.hpp"

class Image {
private:
    size_t width_;
    size_t height_;
    std::vector<PixelDouble> pixels_;

public:
    Image(size_t width, size_t height);

    const size_t GetWidth() const;
    const size_t GetHeight() const;

    PixelDouble& At(size_t x, size_t y);
    const PixelDouble& At(size_t x, size_t y) const;
};
