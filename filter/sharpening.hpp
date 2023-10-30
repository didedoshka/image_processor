#include "apply_matrix.hpp"

class Sharpening : public ApplyMatrix {
public:
    Sharpening();

private:
    static const Pixel::Channel CENTRAL;
};
