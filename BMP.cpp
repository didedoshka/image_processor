#include "BMP.hpp"

#include <exception>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "pixel.hpp"

size_t FourCharsToSizeT(const unsigned char* start) {
    return static_cast<size_t>(start[0] + (start[1] << 8) + (start[2] << 16) + (start[3] << 24));
}

size_t TwoCharsToSizeT(const unsigned char* start) {
    return static_cast<size_t>(start[0] + (start[1] << 8));
}

BMP::BMP(const std::string& path) {
    std::ifstream input;
    try {
        input = std::ifstream(path, std::ios::binary);
    } catch (...) {
        // TODO
    }

    data_ = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    size_t supposed_data_size = FourCharsToSizeT(&data_[2]);
    if (data_.size() < 14 || data_.size() < 2 || data_[0] != 'B' || data_[1] != 'M' ||
        data_.size() != supposed_data_size) {
        throw std::runtime_error("Input BMP file is corrupted");
    }
    size_t supposed_dib_header_size = FourCharsToSizeT(&data_[14]);
    if (supposed_dib_header_size != 40) {
        throw std::runtime_error("DIB in input BMP file is not BITMAPINFOHEADER");
    }
    size_t bits_per_pixel = TwoCharsToSizeT(&data_[28]);
    if (bits_per_pixel != 24) {
        throw std::runtime_error("Image is not 24 bits per pixel");
    }
    size_t compression_method = FourCharsToSizeT(&data_[30]);
    if (compression_method != 0) {
        throw std::runtime_error("Image is compressed");
    }
}

Image BMP::GetImage() const {
    Image image(FourCharsToSizeT(&data_[18]), FourCharsToSizeT(&data_[22]));
    size_t pixel_array_offset = FourCharsToSizeT(&data_[10]);
    size_t row_size = (24 * image.GetWidth() + 31) / 32 * 4;
    for (size_t row = 0; row < image.GetHeight(); row++) {
        for (size_t pixel_in_row = 0; pixel_in_row < image.GetWidth(); ++pixel_in_row) {
            image.At(pixel_in_row, row) =
                PixelDouble(data_[pixel_array_offset + row * row_size + pixel_in_row * 3 + 2],
                            data_[pixel_array_offset + row * row_size + pixel_in_row * 3 + 1],
                            data_[pixel_array_offset + row * row_size + pixel_in_row * 3]);
        }
    }
    return image;
}
