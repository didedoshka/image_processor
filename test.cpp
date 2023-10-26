#include <catch.hpp>
#include <pixel.hpp>
#include <image.hpp>
#include "BMP.hpp"
#include <iostream>

TEST_CASE("Pixel") {
    PixelDouble pixel_double(static_cast<uint8_t>(204), static_cast<uint8_t>(204), static_cast<uint8_t>(102));

    REQUIRE(pixel_double.green == 0.8);
    REQUIRE(pixel_double.green == 0.8);
    REQUIRE(pixel_double.blue == 0.4);
}

TEST_CASE("EmptyImage") {
    Image img(100, 100);

    REQUIRE(img.GetWidth() == 100);
    REQUIRE(img.GetHeight() == 100);

    PixelDouble gray(0.5, 0.5, 0.5);

    REQUIRE(img.At(5, 1).red == 0.0);
    img.At(5, 1) = gray;
    REQUIRE(img.At(5, 1).blue == 0.5);

    const Image const_img(10, 10);

    REQUIRE(const_img.At(5, 5).red == 0.0);
}

TEST_CASE("BMPInput") {
    BMP bmp("../../tasks/image_processor/test_script/data/flag.bmp");

    REQUIRE(true); // TODO
}

TEST_CASE("BMPToImage") {
    BMP bmp("../../tasks/image_processor/test_script/data/flag.bmp");

    Image img = bmp.GetImage();

    REQUIRE(true); // TODO
}
