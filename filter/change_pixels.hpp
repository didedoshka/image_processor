#pragma once

#include "filter.hpp"
#include <functional>

class ChangePixels : public virtual Filter {
public:
    Image operator()(const Image& image) override;

protected:
    std::function<PixelDouble(PixelDouble)> change_pixel_;
};
