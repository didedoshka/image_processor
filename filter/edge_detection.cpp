#include "edge_detection.hpp"
#include "apply_matrix.hpp"
#include "change_pixels.hpp"
#include "grayscale.hpp"

std::vector<std::unique_ptr<Filter>> EdgeDetection::GetFilters(Pixel::Channel threshold) {
    std::vector<std::unique_ptr<Filter>> filters;

    filters.emplace_back(new Grayscale());
    filters.emplace_back(new ApplyMatrix({{0, -1, -1}, {-1, 0, -1}, {0, 0, 4}, {1, 0, -1}, {0, 1, -1}}));
    filters.emplace_back(new ChangePixels([threshold](const Pixel& pixel) {
        if (pixel.GetRed() < threshold) {
            return Pixel(Pixel::Channel{0}, Pixel::Channel{0}, Pixel::Channel{0});
        }
        return Pixel(Pixel::Channel{1}, Pixel::Channel{1}, Pixel::Channel{1});
    }));

    return filters;
}

EdgeDetection::EdgeDetection(Pixel::Channel threshold) : CombinedFilter(GetFilters(threshold)) {
}
