#include "edge_detection.hpp"
#include <iostream>

ApplyEdgeDetectionMatrix::ApplyEdgeDetectionMatrix() {
    const Pixel::Channel central = 4;
    matrix_ = {{0, -1, -1}, {-1, 0, -1}, {0, 0, central}, {1, 0, -1}, {0, 1, -1}};
}

ChangeEdgeDetectionPixels::ChangeEdgeDetectionPixels(Pixel::Channel threshold) {
    change_pixel_ = [threshold](Pixel pixel) {
        if (pixel.GetRed() > threshold) {
            return Pixel(1.0f, 1.0f, 1.0f);
        }
        return Pixel();
    };
}
