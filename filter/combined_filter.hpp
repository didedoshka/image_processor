#pragma once

#include "filter.hpp"

class CombinedFilter : public Filter {
public:
    explicit CombinedFilter(std::vector<std::unique_ptr<Filter>> filters);
    Image operator()(const Image& image) override;

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
