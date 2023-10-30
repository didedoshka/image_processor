#include "gaussian_blur.hpp"
#include <cmath>
#include <numbers>
#include "apply_matrix.hpp"

std::vector<std::unique_ptr<Filter>> GaussianBlur::GetFilters(Pixel::Channel sigma) {
    std::vector<std::unique_ptr<Filter>> filters;

    Image::SizeType border = std::ceil(3 * sigma);
    ApplyMatrix::Matrix matrix;
    matrix.reserve(2 * border + 1);
    for (Image::SizeType delta_row = -border; delta_row <= border; ++delta_row) {
        matrix.push_back({delta_row, 0,
                          std::sqrt(std::numbers::inv_pi_v<Pixel::Channel> / (2 * sigma * sigma)) *
                              std::exp(-static_cast<Pixel::Channel>(delta_row * delta_row) / (2 * sigma * sigma))});
    }
    filters.emplace_back(new ApplyMatrix(matrix));
    matrix.clear();
    matrix.reserve(2 * border + 1);
    for (Image::SizeType delta_column = -border; delta_column <= border; ++delta_column) {
        matrix.push_back(
            {0, delta_column,
             std::sqrt(std::numbers::inv_pi_v<Pixel::Channel> / (2 * sigma * sigma)) *
                 std::exp(-static_cast<Pixel::Channel>(delta_column * delta_column) / (2 * sigma * sigma))});
    }
    filters.emplace_back(new ApplyMatrix(matrix));
    return filters;
}

GaussianBlur::GaussianBlur(Pixel::Channel sigma) : CombinedFilter(GetFilters(sigma)) {
}
