#pragma once

#include <string>
size_t FourCharsToSizeT(unsigned char* start);

class BMP {
public:
    explicit BMP(const std::string& path);
};
