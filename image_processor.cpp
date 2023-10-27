#include "BMP.hpp"
#include "pixel.hpp"
#include "image.hpp"
#include <exception>
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
                     "Edge Detection (-edge threshold) -- detects the edges, threshold is a number between 0 and 1 "
                     "that determines what is considered an edge\n"
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

    try {
        BMP input(input_path);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << ' ' << "Aborting." << '\n';
        return 1;
    } catch (...) {
        std::cout << "Unexpected error occured. Aborting" << '\n';
        return 1;
    }

    std::string output_path;
    arguments >> output_path;
    if (arguments.fail()) {
        std::cout << "Error parsing path to output file. Aborting." << '\n';
        return 1;
    }

    while (!arguments.fail()) {
        std::string filter_name;
        arguments >> filter_name;
        if (arguments.fail()) {
            std::cout << "Error parsing filter name. Aborting." << '\n';
            return 1;
        }
        if (filter_name == "-crop") {
            size_t width = 0;
            size_t height = 0;
            arguments >> width;
            if (arguments.fail()) {
                std::cout << "Error parsing parameter width for filter Crop. Aborting." << '\n';
                return 1;
            }
            arguments >> height;
            if (arguments.fail()) {
                std::cout << "Error parsing parameter height for filter Crop. Aborting." << '\n';
                return 1;
            }
            image = Crop(image, width, height);
        }
    }

    return 0;
}
