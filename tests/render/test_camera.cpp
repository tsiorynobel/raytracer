#include <catch2/catch_test_macros.hpp>
#include "render/camera.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

// Screen 5 wide for a 5 x 3 image: one pixel is 1 x 1.
// Pixel (column, row) is at x = column + 0.5 - 2.5, y = -(row + 0.5 - 1.5).

TEST_CASE("The ray through the middle pixel goes through the screen centre", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5.0);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("The ray through the top-right pixel goes up and to the right", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5.0);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(2, 1, 1));
}

TEST_CASE("The ray through the bottom-left pixel goes down and to the left", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5.0);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(-2, -1, 1));
}

TEST_CASE("Pixels get smaller when the image gets bigger", "[camera]") {
    // Screen 2 wide for 512 x 256: a pixel is 2 / 512 = 1 / 256.
    // x = (511.5 - 256) / 256 = 511 / 512, y = -(0.5 - 128) / 256 = 255 / 512
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);

    Ray ray = camera.rayThroughPixel(511, 0, 512, 256);

    requireVectorsEqual(ray.direction(), Vector(511.0 / 512.0, 255.0 / 512.0, 1));
}

TEST_CASE("Pixels are placed around the screen centre", "[camera]") {
    // Screen centre (0, 0, 1): the top-right pixel is at (2, 1, 1), so D = (2, 1, 2).
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 1), 5.0);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(2, 1, 2));
}

// Screen 5 wide for a 5 x 3 image, red sphere at (0, 0, 6), radius 5.
// L = (0, 0, -7), b = -14, c = 24, discriminant = 196 - 96a: a hit only when a <= 2.
// a = 1 + x^2 + y^2, so the hits are the centre and its four neighbours: a red plus.

TEST_CASE("Rendering draws the pixels whose ray hits the sphere", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5.0);
    const FlatShader red(Colour(1, 0, 0));
    Sphere sphere(Vector(0, 0, 6), 5, red);

    Image image = camera.render(sphere, 5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 5; ++column) {
            bool inPlus = (column == 2 && row != 1) || (row == 1 && column >= 1 && column <= 3);
            Colour expected = inPlus ? Colour(1, 0, 0) : Colour(0, 0, 0);
            requireColoursEqual(image.pixel(column, row), expected);
        }
    }
}

TEST_CASE("Rendering fills every pixel, up to the last row and column", "[camera]") {
    // Screen 3 wide, 3 x 3 image, radius 9 at (0, 0, 9): c = 100 - 81 = 19.
    // Corner: a = 3, discriminant = 400 - 228 = 172. Edge: a = 2, discriminant = 248.
    // Both roots positive: every pixel hits.
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 3.0);
    const FlatShader red(Colour(1, 0, 0));
    Sphere sphere(Vector(0, 0, 9), 9, red);

    Image image = camera.render(sphere, 3, 3);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            requireColoursEqual(image.pixel(column, row), Colour(1, 0, 0));
        }
    }
}
