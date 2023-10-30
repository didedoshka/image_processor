#pragma once

#include "change_pixels.hpp"

class Grayscale : public virtual ChangePixels {
public:
    Grayscale();

private:
    static const Pixel WEIGHTS;
};
