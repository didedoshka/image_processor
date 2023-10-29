#pragma once

#include "filter/filter.hpp"

class Crop : virtual Filter {
public:
    Image operator()(const Image& image) override;
    Crop(Image::SizeType width, Image::SizeType height);

private:
    Image::SizeType width_;
    Image::SizeType height_;
};
