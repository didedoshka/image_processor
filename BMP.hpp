#pragma once

#include <cstdint>
#include <string>
#include "image.hpp"

struct BMPHeader {
    uint8_t magic[2]{'B', 'M'};
    uint32_t file_size{};
    uint8_t depends_on_creator[4]{};
    uint32_t bitmap_offset{54};
};

struct BitmapInfoHeader {
    uint32_t header_size{40};
    int32_t bitmap_width{};
    int32_t bitmap_height{};
    uint16_t color_planes_number{1};
    uint16_t bits_per_pixel{24};
    uint32_t compression{0};
    uint32_t image_size{0};
    int32_t horizontal_resolution{0};
    int32_t vertical_resolution{0};
    uint32_t colors_in_the_palette{0};
    uint32_t important_colors{0};
};

class BMP {
public:
    explicit BMP(const std::string& path);
    Image GetImage() const;
    void Save(const Image& image);

private:
    std::string path_;
    size_t GetRowSize(uint16_t bits_per_pixel, uint32_t bitmap_width);
};
