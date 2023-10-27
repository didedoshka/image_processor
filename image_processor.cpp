#include "pixel.hpp"
#include "image.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Image processor by didedoshka\n"
                     "\n"
                     "To get this message, run ./image_processor\n"
                     "\n"
                     "Run with\n"
                     "./image_processor path/to/input.bmp path/to/output.bmp\n"
                     "[-{filter1} [parameter1] [parameter2] ...]\n"
                     "[-{filter2} [parameter1] [parameter2] ...] ...\n"
                     "\n"
                     "List of filters:\n"
                     "Crop (-crop width height) -- crops image to a given width and height\n"
                     "Grayscale (-gs) -- transforms image to grayscale\n"
                     "Negative (-neg) -- transforms image to negative\n"
                     "Sharpening (-sharp) -- increases sharpness\n"
                     "Edge Detection (-edge threshold) -- detects the edges, threshold is a number between 0 and 255 "
                     "that determens what is considered an edge\n"
                     "Gaussian Blur (-blur sigma) -- applies Gaussian blur with the given sigma\n";
        return 0;
    }
    std::stringstream arguments;
    for (size_t i = 1; i < argc; ++i) {
        arguments << argv[i] << ' ';
    }
    std::string input_path;
    arguments >> input_path;
    if (arguments.fail()) {
        std::cout << "Error parsing path to input file. Aborting." << '\n';
        return 1;
    }
    std::string output_path;
    arguments >> output_path;
    if (arguments.fail()) {
        std::cout << "Error parsing path to output file. Aborting." << '\n';
        return 1;
    }
    std::ifstream file("flag2.bmp");
    std::cout << file.fail() << '\n';

    return 0;
}
