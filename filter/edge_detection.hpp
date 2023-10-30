#pragma once

#include "combined_filter.hpp"

class EdgeDetection : public CombinedFilter {
public:
    explicit EdgeDetection(Pixel::Channel threshold);

private:
    std::vector<std::unique_ptr<Filter>> GetFilters(Pixel::Channel threshold);
};
