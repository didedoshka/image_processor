#include "gaussian_blur.hpp"
#include <cmath>
#include <numbers>

GaussianBlurHorizontal::GaussianBlurHorizontal(Pixel::Channel sigma) {
    Image::SizeType border = std::ceil(3 * sigma);
    matrix_.reserve((2 * border + 1) * (2 * border + 1));
    for (Image::SizeType delta_row = -border; delta_row <= border; ++delta_row) {
        matrix_.push_back({delta_row, 0,
                           std::sqrt(std::numbers::inv_pi_v<Pixel::Channel> / (2 * sigma * sigma)) *
                               std::exp(-static_cast<Pixel::Channel>(delta_row * delta_row) / (2 * sigma * sigma))});
    }
}

GaussianBlurVertical::GaussianBlurVertical(Pixel::Channel sigma) {
    Image::SizeType border = std::ceil(3 * sigma);
    matrix_.reserve((2 * border + 1) * (2 * border + 1));
    for (Image::SizeType delta_column = -border; delta_column <= border; ++delta_column) {
        matrix_.push_back({ 0,delta_column,
                           std::sqrt(std::numbers::inv_pi_v<Pixel::Channel> / (2 * sigma * sigma)) *
                               std::exp(-static_cast<Pixel::Channel>(delta_column * delta_column) / (2 * sigma * sigma))});
    }
}
