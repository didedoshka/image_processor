#pragma once

#include <vector>
#include "pixel.hpp"

class Image {
private:
    uint32_t width_;
    uint32_t height_;
    std::vector<PixelDouble> pixels_;

public:
    Image(uint32_t width, uint32_t height);

    const uint32_t GetWidth() const;
    const uint32_t GetHeight() const;

    PixelDouble& At(uint32_t row, uint32_t column);
    const PixelDouble& At(uint32_t row, uint32_t column) const;
};
