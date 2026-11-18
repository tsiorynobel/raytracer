#include <catch2/catch_test_macros.hpp>
#include "render/image.h"
#include "test_helpers.h"

TEST_CASE("setPixel sets one pixel, all others remain black", "[image]") {
    Image image(5, 4);
    Colour red(1.0, 0.0, 0.0);

    image.setPixel(3, 2, red);

    for (unsigned int y = 0; y < 4; ++y) {
        for (unsigned int x = 0; x < 5; ++x) {
            if (x == 3 && y == 2) {
                requireColoursEqual(image.pixel(x, y), red);
            } else {
                requireColoursEqual(image.pixel(x, y), Colour(0.0, 0.0, 0.0));
            }
        }
    }
}
