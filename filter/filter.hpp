#pragma once
#include "image.hpp"

class Filter {
public:
    Image operator()(const Image& image);
};
