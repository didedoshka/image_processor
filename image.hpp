#pragma once

#include <vector>
#include "pixel.hpp"
#include "BMP.hpp"

class Image {
private:
    size_t width_;
    size_t height_;
    std::vector<PixelDouble> pixels_;

public:
    Image(size_t width, size_t height);
    explicit Image(const BMP& bmp);

    const size_t Width() const;
    const size_t Height() const;

    PixelDouble& At(size_t x, size_t y);
    const PixelDouble& At(size_t x, size_t y) const;
};
