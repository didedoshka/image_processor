#include "apply_matrix.hpp"
#include <iostream>
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
    size_t operations =
        2 * 3 * static_cast<size_t>(image.GetHeight()) * static_cast<size_t>(image.GetWidth()) *
        matrix_.size();  // addition and multiplication for each channel for each pixel for every element in matrix
    const size_t operations_per_second = 500'000'000;  // Compiling in Release mode
    if (operations >= operations_per_second) {
        std::cout << "Applying this filter to this picture is going to take long, approximately "
                  << static_cast<float>(operations) / static_cast<float>(operations_per_second) << " seconds" << '\n';
    } else if (operations >= 10 * 60 * operations_per_second) {
        std::cout << "Applying this filter to this picture is going to take extremely long, approximately "
                  << static_cast<float>(operations) / static_cast<float>(operations_per_second) / 60 << " minutes"
                  << '\n';
    } else if (operations >= 60 * 60 * operations_per_second) {
        throw std::runtime_error{"Applying this filter is going to take more than an hour"};
    }
    Image result(image.GetWidth(), image.GetHeight());

    for (Image::SizeType row = 0; row < result.GetHeight(); ++row) {
        for (Image::SizeType column = 0; column < result.GetWidth(); ++column) {
            Pixel::Channel red = 0.0;
            Pixel::Channel green = 0.0;
            Pixel::Channel blue = 0.0;
            for (auto [row_delta, column_delta, weight] : matrix_) {
                auto [nearest_row, nearest_column] =
                    GetNearest(row + row_delta, column + column_delta, image.GetWidth(), image.GetHeight());
                red += weight * image.At(nearest_row, nearest_column).GetRed();
                green += weight * image.At(nearest_row, nearest_column).GetGreen();
                blue += weight * image.At(nearest_row, nearest_column).GetBlue();
            }
            result.At(row, column) = Pixel(red, green, blue);
        }
    }

    return result;
}
