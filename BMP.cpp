#include "BMP.hpp"

#include <cstdint>
#include <exception>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include "pixel.hpp"

Image::SizeType BMP::GetRowSize(uint16_t bits_per_pixel, uint32_t bitmap_width) {
    return (static_cast<Image::SizeType>(bits_per_pixel) * static_cast<Image::SizeType>(bitmap_width) + 31) / 32 * 4;
}

BMP::BMP(const std::string& path) : path_(path) {
}

void Read(std::ifstream& ifs, auto& data) {
    ifs.read(reinterpret_cast<char*>(&data), sizeof(data));
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

    std::streamsize bitmap_size = bmp_header.file_size - bmp_header.bitmap_offset;
    std::unique_ptr<uint8_t> bitmap(new uint8_t[bitmap_size]);

    input.read(reinterpret_cast<char*>(bitmap.get()), bitmap_size);
    if (input.fail()) {
        throw std::runtime_error("Input file is too small: bitmap doen't fit.");
    }

    Image image(bitmap_info_header.bitmap_width, bitmap_info_header.bitmap_height);
    Image::SizeType row_size = GetRowSize(bitmap_info_header.bits_per_pixel, bitmap_info_header.bitmap_width);
    for (Image::SizeType row = 0; row < image.GetHeight(); row++) {
        for (Image::SizeType column = 0; column < image.GetWidth(); ++column) {
            image.At(image.GetHeight() - row - 1, column) =
                Pixel(bitmap.get()[row * row_size + column * 3 + 2], bitmap.get()[row * row_size + column * 3 + 1],
                      bitmap.get()[row * row_size + column * 3]);
        }
    }
    return image;
}

void BMP::Save(const Image& image) {
    BMPHeader bmp_header;
    BitmapInfoHeader bitmap_info_header;
    bitmap_info_header.bitmap_width = static_cast<int32_t>(image.GetWidth());
    bitmap_info_header.bitmap_height = static_cast<int32_t>(image.GetHeight());
    Image::SizeType row_size = GetRowSize(bitmap_info_header.bits_per_pixel, bitmap_info_header.bitmap_width);
    bmp_header.file_size = (bmp_header.bitmap_offset + bitmap_info_header.bitmap_height * row_size);

    std::streamsize bitmap_size = bmp_header.file_size - bmp_header.bitmap_offset;
    std::unique_ptr<uint8_t> bitmap(new uint8_t[bitmap_size]);
    for (Image::SizeType row = 0; row < image.GetHeight(); row++) {
        for (Image::SizeType column = 0; column < image.GetWidth(); ++column) {
            Pixel current = image.At(image.GetHeight() - row - 1, column);
            bitmap.get()[row * row_size + column * 3 + 2] = Pixel::ChannelToUInt8T(current.GetRed());
            bitmap.get()[row * row_size + column * 3 + 1] = Pixel::ChannelToUInt8T(current.GetGreen());
            bitmap.get()[row * row_size + column * 3] = Pixel::ChannelToUInt8T(current.GetBlue());
        }
    }

    std::ofstream output(path_, std::ios::binary);
    output.write(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    output.write(reinterpret_cast<char*>(&bitmap_info_header), sizeof(bitmap_info_header));
    output.write(reinterpret_cast<char*>(bitmap.get()), bitmap_size);
    if (output.fail()) {
        throw std::runtime_error("Error occured while saving the file.");
    }
}
