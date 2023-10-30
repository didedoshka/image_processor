#include "BMP.hpp"

#include <climits>
#include <cstdint>
#include <exception>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include "pixel.hpp"

Image::SizeType BMP::GetRowSize(uint16_t bits_per_pixel, uint32_t bitmap_width) {
    const Image::SizeType four_bytes = 32;
    return (static_cast<Image::SizeType>(bits_per_pixel) * static_cast<Image::SizeType>(bitmap_width) +
            (four_bytes - 1)) /
           four_bytes * 4;
}

BMP::BMP(const std::string& path) : path_(path) {
}

void BMP::ReadNumber(std::ifstream& ifs, auto& number, size_t size) {
    uint8_t byte = 0;
    number = 0;
    for (size_t i = 0; i < size; ++i) {
        ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        number ^= (byte << (i * CHAR_BIT));
    }
    if (ifs.fail()) {
        throw std::runtime_error{"Error occured while reading from file"};
    }
}

void BMP::WriteNumber(std::ofstream& ofs, auto& number, size_t size) {
    char byte = 0;
    for (size_t i = 0; i < size; ++i) {
        byte = ((number << ((size - i - 1) * CHAR_BIT)) >> ((size - 1) * CHAR_BIT));
        ofs.write(reinterpret_cast<char*>(&byte), sizeof(byte));
    }
    if (ofs.fail()) {
        throw std::runtime_error{"Error occured while saving file"};
    }
}

Image BMP::GetImage() const {
    std::ifstream input = std::ifstream(path_, std::ios::binary);
    if (input.fail()) {
        throw std::runtime_error{"Can't load input file."};
    }

    BMPHeader bmp_header;
    BMP::ReadNumber(input, bmp_header.magic, sizeof(bmp_header.magic));
    BMP::ReadNumber(input, bmp_header.file_size, sizeof(bmp_header.file_size));
    BMP::ReadNumber(input, bmp_header.depends_on_creator, sizeof(bmp_header.depends_on_creator));
    BMP::ReadNumber(input, bmp_header.bitmap_offset, sizeof(bmp_header.bitmap_offset));

    if (input.fail()) {
        throw std::runtime_error{"Input file is too small: Bitmap file header dosn't fit."};
    }

    if (bmp_header.magic != SUPPORTED_MAGIC) {
        throw std::runtime_error{"Input file is not BMP."};
    }

    if (bmp_header.bitmap_offset != SUPPORTED_BITMAP_OFFSET) {
        throw std::runtime_error{"Input file uses wrong Bitmap file header or DIB header."};
    }

    BitmapInfoHeader bitmap_info_header;

    BMP::ReadNumber(input, bitmap_info_header.header_size, sizeof(bitmap_info_header.header_size));
    BMP::ReadNumber(input, bitmap_info_header.bitmap_width, sizeof(bitmap_info_header.bitmap_width));
    BMP::ReadNumber(input, bitmap_info_header.bitmap_height, sizeof(bitmap_info_header.bitmap_height));
    BMP::ReadNumber(input, bitmap_info_header.color_planes_number, sizeof(bitmap_info_header.color_planes_number));
    BMP::ReadNumber(input, bitmap_info_header.bits_per_pixel, sizeof(bitmap_info_header.bits_per_pixel));
    BMP::ReadNumber(input, bitmap_info_header.compression, sizeof(bitmap_info_header.compression));
    BMP::ReadNumber(input, bitmap_info_header.image_size, sizeof(bitmap_info_header.image_size));
    BMP::ReadNumber(input, bitmap_info_header.horizontal_resolution, sizeof(bitmap_info_header.horizontal_resolution));
    BMP::ReadNumber(input, bitmap_info_header.vertical_resolution, sizeof(bitmap_info_header.vertical_resolution));
    BMP::ReadNumber(input, bitmap_info_header.colors_in_the_palette, sizeof(bitmap_info_header.colors_in_the_palette));
    BMP::ReadNumber(input, bitmap_info_header.important_colors, sizeof(bitmap_info_header.important_colors));

    if (input.fail()) {
        throw std::runtime_error{"Input file is too small: BITMAPINFOHEADER dosn't fit."};
    }
    if (bitmap_info_header.header_size != SUPPORTED_HEADER_SIZE) {
        throw std::runtime_error("DIB header in input BMP file is not BITMAPINFOHEADER.");
    }
    if (bitmap_info_header.color_planes_number != 1) {
        throw std::runtime_error("The amount of color planes does not equal one.");
    }
    if (bitmap_info_header.bits_per_pixel != SUPPORTED_BITS_PER_PIXEL) {
        throw std::runtime_error("Image is not 24 bits per pixel.");
    }
    if (bitmap_info_header.compression != 0) {
        throw std::runtime_error("Image is compressed.");
    }
    if (bitmap_info_header.colors_in_the_palette != 0 &&
        bitmap_info_header.colors_in_the_palette != (1 << bitmap_info_header.bits_per_pixel)) {
        throw std::runtime_error("There are not 2^24 colors in the pallete.");
    }

    std::streamsize bitmap_size = bmp_header.file_size - bmp_header.bitmap_offset;
    std::unique_ptr<uint8_t[]> bitmap(new uint8_t[bitmap_size]);

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
    std::ofstream output(path_, std::ios::binary);
    if (output.fail()) {
        throw std::runtime_error{"Can't load output file."};
    }
    BMPHeader bmp_header;
    BitmapInfoHeader bitmap_info_header;

    bitmap_info_header.bitmap_width = static_cast<int32_t>(image.GetWidth());
    bitmap_info_header.bitmap_height = static_cast<int32_t>(image.GetHeight());
    Image::SizeType row_size = GetRowSize(bitmap_info_header.bits_per_pixel, bitmap_info_header.bitmap_width);
    bmp_header.file_size = (bmp_header.bitmap_offset + bitmap_info_header.bitmap_height * row_size);

    BMP::WriteNumber(output, bmp_header.magic, sizeof(bmp_header.magic));
    BMP::WriteNumber(output, bmp_header.file_size, sizeof(bmp_header.file_size));
    BMP::WriteNumber(output, bmp_header.depends_on_creator, sizeof(bmp_header.depends_on_creator));
    BMP::WriteNumber(output, bmp_header.bitmap_offset, sizeof(bmp_header.bitmap_offset));
    BMP::WriteNumber(output, bitmap_info_header.header_size, sizeof(bitmap_info_header.header_size));
    BMP::WriteNumber(output, bitmap_info_header.bitmap_width, sizeof(bitmap_info_header.bitmap_width));
    BMP::WriteNumber(output, bitmap_info_header.bitmap_height, sizeof(bitmap_info_header.bitmap_height));
    BMP::WriteNumber(output, bitmap_info_header.color_planes_number, sizeof(bitmap_info_header.color_planes_number));
    BMP::WriteNumber(output, bitmap_info_header.bits_per_pixel, sizeof(bitmap_info_header.bits_per_pixel));
    BMP::WriteNumber(output, bitmap_info_header.compression, sizeof(bitmap_info_header.compression));
    BMP::WriteNumber(output, bitmap_info_header.image_size, sizeof(bitmap_info_header.image_size));
    BMP::WriteNumber(output, bitmap_info_header.horizontal_resolution,
                     sizeof(bitmap_info_header.horizontal_resolution));
    BMP::WriteNumber(output, bitmap_info_header.vertical_resolution, sizeof(bitmap_info_header.vertical_resolution));
    BMP::WriteNumber(output, bitmap_info_header.colors_in_the_palette,
                     sizeof(bitmap_info_header.colors_in_the_palette));
    BMP::WriteNumber(output, bitmap_info_header.important_colors, sizeof(bitmap_info_header.important_colors));

    std::streamsize bitmap_size = bmp_header.file_size - bmp_header.bitmap_offset;
    std::unique_ptr<uint8_t[]> bitmap(new uint8_t[bitmap_size]);
    for (Image::SizeType row = 0; row < image.GetHeight(); row++) {
        for (Image::SizeType column = 0; column < image.GetWidth(); ++column) {
            Pixel current = image.At(image.GetHeight() - row - 1, column);
            bitmap.get()[row * row_size + column * 3 + 2] = Pixel::ChannelToUInt8T(current.GetRed());
            bitmap.get()[row * row_size + column * 3 + 1] = Pixel::ChannelToUInt8T(current.GetGreen());
            bitmap.get()[row * row_size + column * 3] = Pixel::ChannelToUInt8T(current.GetBlue());
        }
    }

    output.write(reinterpret_cast<char*>(bitmap.get()), bitmap_size);
    if (output.fail()) {
        throw std::runtime_error("Error occured while saving file.");
    }
}
