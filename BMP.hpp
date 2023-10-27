#pragma once

#include <string>
#include "image.hpp"


class BMP {
public:
    explicit BMP(const std::string& path);
    Image GetImage() const;
    void Save(const Image& image);

private:
    std::string path_;
};
