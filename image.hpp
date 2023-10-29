#pragma once

#include <vector>
#include "pixel.hpp"

class Image {

public:
    using SizeType = int32_t;
    Image(SizeType width, SizeType height);

    const SizeType GetWidth() const;
    const SizeType GetHeight() const;

    Pixel& At(SizeType row, SizeType column);
    const Pixel& At(SizeType row, SizeType column) const;

private:
    SizeType width_;
    SizeType height_;
    std::vector<Pixel> pixels_;
};
