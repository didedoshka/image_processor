#pragma once

#include "change_pixels.hpp"

class Grayscale : public ChangePixels {
public:
    Grayscale();

private:
    static const Pixel WEIGHTS;
};
