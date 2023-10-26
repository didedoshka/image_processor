#include "BMP.hpp"

#include <exception>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
size_t FourCharsToSizeT(unsigned char* start) {
    return static_cast<size_t>(start[0] + (start[1] << 8) + (start[2] << 16) + (start[3] << 24));
}

BMP::BMP(const std::string& path) {
    std::ifstream input;
    try {
        input = std::ifstream(path, std::ios::binary);
    } catch (...) {
        // TODO
    }

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    for (size_t i = 0; i < 14; ++i) {
        std::cout << (unsigned)buffer[i] << ' ';
    }
    std::cout << '\n';
    size_t size = FourCharsToSizeT(&buffer[2]);
    if (buffer.size() != size) {
        throw std::runtime_error("Input BMP file is corrupted.");
    }
    // size_t offset =
    // unsigned char a;
    // while (input_file) {
    //     input_file >> a;
    //     std::cout << static_cast<unsigned int>(a) << ' ';
    // }
}
