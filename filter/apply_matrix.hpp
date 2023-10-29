#pragma once

#include <cstdint>
#include <vector>
#include "filter.hpp"

class ApplyMatrix : public virtual Filter {
public:
    struct MatrixElement {
        int8_t row_delta;
        int8_t column_delta;
        int8_t weight;
    };

    using Matrix = std::vector<MatrixElement>;
    Image operator()(const Image& image) override;

private:
    std::pair<Image::SizeType, Image::SizeType> GetNearest(Image::SizeType row, Image::SizeType column,
                                                           Image::SizeType width, Image::SizeType height);

protected:
    Matrix matrix_;
};
