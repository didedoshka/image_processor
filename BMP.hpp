#pragma once

#include <string>
#include <vector>
#include "image.hpp"

size_t FourCharsToSizeT(const unsigned char* start);

class BMP {
public:
    explicit BMP(const std::string& path);
    Image GetImage() const;
    explicit BMP(const Image& image);
    void Save(const std::string& path);

private:
    std::vector<unsigned char> data_;
};
