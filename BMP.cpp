#include "BMP.hpp"

#include <cstdint>
#include <exception>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include "pixel.hpp"


BMP::BMP(const std::string& path) : path_(path) {
}

Image BMP::GetImage() const {
    std::ifstream input = std::ifstream(path_, std::ios::binary);
    if (input.fail()) {
        throw std::runtime_error{"Can't load input file."};
    }

    BMPHeader bmp_header;
    input.read(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    if (input.fail()) {
        throw std::runtime_error{"Input file is too small: Bitmap file header dosn't fit."};
    }

    if (bmp_header.magic[0] != 'B' || bmp_header.magic[1] != 'M') {
        throw std::runtime_error{"Input file is not BMP."};
    }
    if (bmp_header.bitmap_offset != 54) {
        throw std::runtime_error{"Input file uses wrong Bitmap file header or DIB header."};
    }

    BitmapInfoHeader bitmap_info_header;
    input.read(reinterpret_cast<char*>(&bitmap_info_header), sizeof(bitmap_info_header));
    if (input.fail()) {
        throw std::runtime_error{"Input file is too small: BITMAPINFOHEADER dosn't fit."};
    }

    if (bitmap_info_header.header_size != 40) {
        throw std::runtime_error("DIB header in input BMP file is not BITMAPINFOHEADER.");
    }
    if (bitmap_info_header.color_planes_number != 1) {
        throw std::runtime_error("The amount of color planes does not equal one.");
    }
    if (bitmap_info_header.bits_per_pixel != 24) {
        throw std::runtime_error("Image is not 24 bits per pixel.");
    }
    if (bitmap_info_header.compression != 0) {
        throw std::runtime_error("Image is compressed.");
    }
    if (bitmap_info_header.colors_in_the_palette != 0 && bitmap_info_header.colors_in_the_palette != (1 << 24)) {
        throw std::runtime_error("There are not 2^24 colors in the pallete.");
    }

    std::unique_ptr<uint8_t> bitmap(new uint8_t[bmp_header.file_size - bmp_header.bitmap_offset]);

    Image image(bitmap_info_header.bitmap_width, bitmap_info_header.bitmap_height);
    size_t pixel_array_offset = FourCharsToSizeT(&data[10]);
    size_t row_size = (24 * image.GetWidth() + 31) / 32 * 4;
    for (size_t row = 0; row < image.GetHeight(); row++) {
        for (size_t pixel_in_row = 0; pixel_in_row < image.GetWidth(); ++pixel_in_row) {
            image.At(pixel_in_row, row) = PixelDouble(data[pixel_array_offset + row * row_size + pixel_in_row * 3 + 2],
                                                      data[pixel_array_offset + row * row_size + pixel_in_row * 3 + 1],
                                                      data[pixel_array_offset + row * row_size + pixel_in_row * 3]);
        }
    }
    return image;
}
