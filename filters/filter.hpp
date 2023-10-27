#pragma once

#include <cstdint>
#include <vector>
#include "image.hpp"
#include "pixel.hpp"
#include <functional>

struct MatrixElement {
    int8_t dx;
    int8_t dy;
    int8_t weight;
};

using Matrix = std::vector<MatrixElement>;

Image ApplyMatrix(const Image& image, const Matrix& matrix);

Image ChangeEveryPixel(const Image& image, std::function<PixelDouble(const PixelDouble&)>);
