#include "combined_filter.hpp"

class GaussianBlur : public CombinedFilter {
public:
    explicit GaussianBlur(Pixel::Channel sigma);

private:
    std::vector<std::unique_ptr<Filter>> GetFilters(Pixel::Channel sigma);
};
