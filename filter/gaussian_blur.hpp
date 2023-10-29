#include "apply_matrix.hpp"

class GaussianBlur : public virtual ApplyMatrix {
public:
    explicit GaussianBlur(Pixel::Channel sigma);
};
