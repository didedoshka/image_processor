#pragma once

#include "filter.hpp"

class Crop : public virtual Filter {
public:
    Crop(Image::SizeType width, Image::SizeType height);
    Image operator()(const Image& image) override;

private:
    Image::SizeType width_;
    Image::SizeType height_;
};
