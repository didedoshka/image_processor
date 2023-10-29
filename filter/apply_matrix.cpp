#include "apply_matrix.hpp"
#include <stdexcept>


std::pair<Image::SizeType, Image::SizeType> ApplyMatrix::GetNearest(Image::SizeType row, Image::SizeType column,
                                                                    Image::SizeType width, Image::SizeType height) {
    Image::SizeType result_row = row;
    Image::SizeType result_column = column;
    if (row < 0) {
        result_row = 0;
    } else if (row >= height) {
        result_row = height - 1;
    }

    if (column < 0) {
        result_column = 0;
    } else if (column >= width) {
        result_column = width - 1;
    }
    return {result_row, result_column};
}

Image ApplyMatrix::operator()(const Image& image) {
    if (matrix_.empty()) {
        throw std::runtime_error{"Matrix in ApplyMatrix is empty"};
    }
    Image result(image.GetWidth(), image.GetHeight());

    for (Image::SizeType row = 0; row < result.GetHeight(); ++row) {
        for (Image::SizeType column = 0; column < result.GetWidth(); ++column) {
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            for (auto [row_delta, column_delta, weight] : matrix_) {
                auto [nearest_row, nearest_column] =
                    GetNearest(row + row_delta, column + column_delta, image.GetWidth(), image.GetHeight());
                red += weight * image.At(nearest_row, nearest_column).GetRed();
                green += weight * image.At(nearest_row, nearest_column).GetGreen();
                blue += weight * image.At(nearest_row, nearest_column).GetBlue();
            }
            result.At(row, column) = PixelDouble(red, green, blue);
        }
    }

    return result;
}
