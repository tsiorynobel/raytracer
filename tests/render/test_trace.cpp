#include <catch2/catch_test_macros.hpp>
#include "render/trace.h"
#include "test_helpers.h"

TEST_CASE("A ray that hits the sphere takes the sphere's colour", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Colour pixel = trace(ray, sphere);

    requireColoursEqual(pixel, Colour(1, 0, 0));
}

TEST_CASE("A ray that misses the sphere is black", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));

    Colour pixel = trace(ray, sphere);

    requireColoursEqual(pixel, Colour(0, 0, 0));
}
