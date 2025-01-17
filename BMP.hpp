#pragma once

#include <climits>
#include <cstdint>
#include <fstream>
#include <string>
#include "image.hpp"

const uint16_t SUPPORTED_MAGIC = ('M' << CHAR_BIT) + 'B';
const uint32_t SUPPORTED_BITMAP_OFFSET = 54;
const uint32_t SUPPORTED_HEADER_SIZE = 40;
const uint32_t SUPPORTED_BITS_PER_PIXEL = 24;

struct BMPHeader {
    uint16_t magic{('M' << CHAR_BIT) + 'B'};
    uint32_t file_size{};
    uint32_t depends_on_creator{};
    uint32_t bitmap_offset{SUPPORTED_BITMAP_OFFSET};
};

struct BitmapInfoHeader {
    uint32_t header_size{SUPPORTED_HEADER_SIZE};
    int32_t bitmap_width{};
    int32_t bitmap_height{};
    uint16_t color_planes_number{1};
    uint16_t bits_per_pixel{SUPPORTED_BITS_PER_PIXEL};
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
    static void ReadNumber(std::ifstream& ifs, auto& number, size_t size);
    static void WriteNumber(std::ofstream& ofs, auto& number, size_t size);

    static Image::SizeType GetRowSize(uint16_t bits_per_pixel, uint32_t bitmap_width);
};
