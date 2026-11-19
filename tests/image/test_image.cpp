#include <catch2/catch_test_macros.hpp>
#include "image/image.h"
#include "test_helpers.h"

// A 5 x 3 test image: not square, so swapping width and height shows up.

TEST_CASE("An image knows its width and height", "[image]") {
    Image image(5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("Every pixel of a new image is black", "[image]") {
    Image image(5, 3);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 5; ++column) {
            requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
        }
    }
}

TEST_CASE("Setting a pixel changes only that pixel", "[image]") {
    Image image(5, 3);
    Colour red(1, 0, 0);

    image.setPixel(4, 0, red);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 5; ++column) {
            Colour expected = (column == 4 && row == 0) ? red : Colour(0, 0, 0);
            requireColoursEqual(image.pixel(column, row), expected);
        }
    }
}
