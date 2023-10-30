#include "combined_filter.hpp"
#include <memory>

CombinedFilter::CombinedFilter(std::vector<std::unique_ptr<Filter>> filters) : filters_{std::move(filters)} {
}

Image CombinedFilter::operator()(const Image& image) {
    Image result = image;
    for (std::unique_ptr<Filter>& filter : filters_) {
        result = (*filter)(result);
    }
    return result;
}
