#pragma once

#include "filter.hpp"
#include <functional>

class ChangePixels : public Filter {
public:
    Image operator()(const Image& image) override;

protected:
    std::function<Pixel(Pixel)> change_pixel_;
};
