#include "BMP.hpp"
// #include "filter/apply_matrix.hpp"
#include "pixel.hpp"
#include "image.hpp"
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "filter/filter.hpp"
#include "filter/crop.hpp"
#include "filter/grayscale.hpp"

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

    BMP input_bmp(input_path);

    std::string output_path;
    arguments >> output_path;
    if (arguments.fail()) {
        std::cout << "Error parsing path to output file. Aborting." << '\n';
        return 1;
    }

    BMP output_bmp(output_path);
    Image image{0, 0};
    try {
        image = input_bmp.GetImage();
    } catch (const std::exception& ex) {
        std::cout << "While opening input file an error occured: " << ex.what() << ' ' << "Aborting." << '\n';
        return 1;
    }

    std::vector<std::unique_ptr<Filter>> filter_sequence;

    while (true) {
        std::string filter_name;
        arguments >> filter_name;
        if (arguments.fail()) {
            break;
        }
        if (filter_name == "-crop") {
            Image::SizeType width = 0;
            Image::SizeType height = 0;
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
            filter_sequence.emplace_back(new Crop(width, height));
        } else if (filter_name == "-gs") {
            filter_sequence.emplace_back(new Grayscale());
        }
    }

    for (std::unique_ptr<Filter>& filter : filter_sequence) {
        image = (*filter)(image);
    }

    try {
        output_bmp.Save(image);
    } catch (const std::exception& ex) {
        std::cout << "While saveing a file an error occured: " << ex.what() << ' ' << "Aborting." << '\n';
        return 1;
    }

    return 0;
}
