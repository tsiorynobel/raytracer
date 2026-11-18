#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "render/trace.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("A ray that hits the sphere takes the sphere's colour", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Colour pixel = trace(ray, sphere);

    REQUIRE_THAT(pixel.r(), WithinAbs(1, tolerance));
    REQUIRE_THAT(pixel.g(), WithinAbs(0, tolerance));
    REQUIRE_THAT(pixel.b(), WithinAbs(0, tolerance));
}

TEST_CASE("A ray that misses the sphere is black", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));

    Colour pixel = trace(ray, sphere);

    REQUIRE_THAT(pixel.r(), WithinAbs(0, tolerance));
    REQUIRE_THAT(pixel.g(), WithinAbs(0, tolerance));
    REQUIRE_THAT(pixel.b(), WithinAbs(0, tolerance));
}
