#pragma once

#include <cstdint>
#include <vector>
#include "filter/filter.hpp"

class ApplyMatrix : virtual Filter {
public:
    struct MatrixElement {
        int8_t row_delta;
        int8_t column_delta;
        int8_t weight;
    };

    using Matrix = std::vector<MatrixElement>;
    explicit ApplyMatrix(const Matrix& matrix);
    Image operator()(const Image& image);

private:
    std::pair<Image::SizeType, Image::SizeType> GetNearest(Image::SizeType row, Image::SizeType column, Image::SizeType width, Image::SizeType height);
    Matrix matrix_;
};
