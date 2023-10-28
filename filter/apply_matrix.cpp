#include "filter/apply_matrix.hpp"
#include <stdexcept>

ApplyMatrix::ApplyMatrix(const ApplyMatrix::Matrix& matrix) {
    if (matrix.empty()) {
        throw std::runtime_error{"Matrix for ApplyMatrix is empty."};
    }
    matrix_ = matrix;
}

std::pair<Image::SizeType, Image::SizeType> ApplyMatrix::GetNearest(Image::SizeType row, Image::SizeType column,
                                                                    Image::SizeType width, Image::SizeType height) {
    Image::SizeType result_row = row;
    Image::SizeType result_column = column;
    if (row < 0) {
        result_row = 0;
    } else if (row > height) {
        result_row = height - 1;
    }

    if (column < 0) {
        result_column = 0;
    } else if (column > width) {
        result_column = width - 1;
    }
    return {result_row, result_column};
}

Image ApplyMatrix::operator()(const Image& image) {
    Image result(image.GetWidth(), image.GetHeight());

    for (Image::SizeType row = 0; row < result.GetHeight(); ++row) {
        for (Image::SizeType column = 0; column < result.GetWidth(); ++column) {
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            for (auto [row_delta, column_delta, weight] : matrix_) {
                auto [nearest_row, nearest_column] =
                    GetNearest(row + row_delta, column + column_delta, image.GetWidth(), image.GetHeight());
                red += image.At(nearest_row, nearest_column).GetRed();
                green += image.At(nearest_row, nearest_column).GetGreen();
                blue += image.At(nearest_row, nearest_column).GetBlue();
            }
            red /= static_cast<double>(matrix_.size());
            green /= static_cast<double>(matrix_.size());
            blue /= static_cast<double>(matrix_.size());
            result.At(row, column) = PixelDouble(red, green, blue);
        }
    }

    return result;
}
