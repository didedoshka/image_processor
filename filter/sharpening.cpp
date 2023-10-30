#include "sharpening.hpp"

Sharpening::Sharpening() {
    const Pixel::Channel central = 5;
    matrix_ = {{0, -1, -1}, {-1, 0, -1}, {0, 0, central}, {1, 0, -1}, {0, 1, -1}};
}
