#pragma once

#include "filter.hpp"
#include <functional>

class ChangePixels : public Filter {
public:
    explicit ChangePixels(std::function<Pixel(const Pixel&)> change_pixel);
    Image operator()(const Image& image) override;

private:
    std::function<Pixel(Pixel)> change_pixel_;
};
