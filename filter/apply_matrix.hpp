#pragma once

#include <vector>
#include "filter.hpp"

class ApplyMatrix : public Filter {
public:
    struct MatrixElement {
        Image::SizeType row_delta;
        Image::SizeType column_delta;
        Pixel::Channel weight;
    };

    using Matrix = std::vector<MatrixElement>;
    explicit ApplyMatrix(const Matrix& matrix);
    Image operator()(const Image& image) override;

private:
    std::pair<Image::SizeType, Image::SizeType> GetNearest(Image::SizeType row, Image::SizeType column,
                                                           Image::SizeType width, Image::SizeType height);
    Matrix matrix_;
};
