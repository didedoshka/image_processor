#include "sharpening.hpp"

Sharpening::Sharpening() {
    matrix_ = {{0, -1, -1}, {-1, 0, -1}, {0, 0, 5}, {1, 0, -1}, {0, 1, -1}};
}
