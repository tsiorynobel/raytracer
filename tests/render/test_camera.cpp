#include <catch2/catch_test_macros.hpp>
#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("The ray through the centre goes from the eye to the screen centre", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0));

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("The ray through the centre follows the camera when it moves", "[camera]") {
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1));

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}
