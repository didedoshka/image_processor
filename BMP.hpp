#pragma once

#include <string>
#include <vector>
#include "image.hpp"

size_t FourCharsToSizeT(const unsigned char* start);

class BMP {
public:
    explicit BMP(const std::string& path);
    Image GetImage() const;

private:
    std::vector<unsigned char> data_;
};
