#pragma once

#include <vector>
#include "pixel.hpp"

class Image {

public:
    using SizeType = int32_t;
    Image(SizeType width, SizeType height);

    const SizeType GetWidth() const;
    const SizeType GetHeight() const;

    PixelDouble& At(SizeType row, SizeType column);
    const PixelDouble& At(SizeType row, SizeType column) const;

private:
    SizeType width_;
    SizeType height_;
    std::vector<PixelDouble> pixels_;
};
