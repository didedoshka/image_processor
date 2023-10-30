#include "apply_matrix.hpp"

class GaussianBlurHorizontal : public virtual ApplyMatrix {
public:
    explicit GaussianBlurHorizontal(Pixel::Channel sigma);
};

class GaussianBlurVertical : public virtual ApplyMatrix {
public:
    explicit GaussianBlurVertical(Pixel::Channel sigma);
};
