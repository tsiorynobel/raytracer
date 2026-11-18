#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "io/png_saver.h"
#include "lodepng.h"

TEST_CASE("A saved PNG holds each pixel as red, green, blue and full alpha", "[png]") {
    Image image(2, 1);
    image.setPixel(0, 0, Colour(1, 0, 0));
    image.setPixel(1, 0, Colour(0, 0, 1));

    PngSaver saver;
    saver.save(image, "test_png_saver.png");

    std::vector<unsigned char> pixels;
    unsigned int width = 0;
    unsigned int height = 0;
    REQUIRE(lodepng::decode(pixels, width, height, "test_png_saver.png") == 0);

    REQUIRE(width == 2);
    REQUIRE(height == 1);
    REQUIRE(pixels == std::vector<unsigned char>{255, 0, 0, 255, 0, 0, 255, 255});
}
