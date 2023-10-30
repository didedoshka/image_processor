#include <catch.hpp>
#include <pixel.hpp>
#include <image.hpp>
#include "BMP.hpp"
#include <iostream>

TEST_CASE("Pixel") {
    Pixel pixel(uint8_t(204), uint8_t(204), uint8_t(102));

    REQUIRE(pixel.GetRed() - 0.8 < 0.0001);
    REQUIRE(pixel.GetGreen() - 0.8 < 0.0001);
    REQUIRE(pixel.GetBlue() - 0.4 < 0.0001);
}

TEST_CASE("EmptyImage") {
    Image img(100, 100);

    REQUIRE(img.GetWidth() == 100);
    REQUIRE(img.GetHeight() == 100);

    Pixel gray(0.5f, 0.5f, 0.5f);

    REQUIRE(img.At(5, 1).GetRed() == 0.0);
    img.At(5, 1) = gray;
    REQUIRE(img.At(5, 1).GetBlue() == 0.5);

    const Image const_img(10, 10);

    REQUIRE(const_img.At(5, 5).GetRed() == 0.0);
}
