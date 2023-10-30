#include "sharpening.hpp"
#include "apply_matrix.hpp"

const Pixel::Channel Sharpening::CENTRAL = 5;

Sharpening::Sharpening()
    : ApplyMatrix({{0, -1, -1}, {-1, 0, -1}, {0, 0, Sharpening::CENTRAL}, {1, 0, -1}, {0, 1, -1}}) {
}
