#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "output/png_saver.h"
#include "lodepng.h"

TEST_CASE("A saved PNG holds one rounded RGB byte triple per pixel, row by row", "[png]") {
    // 2 x 2 image, black except (1, 0) = (1, 0.5, 0).
    // 0.5 * 255 = 127.5, rounded to 128.
    Image image(2, 2);
    image.setPixel(1, 0, Colour(1, 0.5, 0));

    const PngSaver saver;
    saver.save(image, "test_png_saver.png");

    std::vector<unsigned char> bytes;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int error = lodepng::decode(bytes, width, height, "test_png_saver.png", LCT_RGB);

    REQUIRE(error == 0);
    REQUIRE(width == 2);
    REQUIRE(height == 2);

    std::vector<int> actual(bytes.begin(), bytes.end());
    REQUIRE(actual == std::vector<int>{0, 0, 0, 255, 128, 0, 0, 0, 0, 0, 0, 0});
}
