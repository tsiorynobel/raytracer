#include <catch2/catch_test_macros.hpp>
#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("The ray through the centre goes from the eye to the screen centre", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2.0);

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("The ray through the centre follows the camera when it moves", "[camera]") {
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1), 2.0);

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}

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
