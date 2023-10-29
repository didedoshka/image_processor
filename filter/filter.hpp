#pragma once
#include "../image.hpp"

class Filter {
public:
    virtual Image operator()(const Image& image) = 0;
    virtual ~Filter() = default;
};

