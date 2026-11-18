#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/sphere.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

// Expected values from L = O - C, a = D.D, b = 2 D.L, c = L.L - r^2,
// discriminant = b^2 - 4ac, t = (-b +- sqrt(discriminant)) / 2a.

TEST_CASE("A ray through the centre of the sphere hits it", "[sphere]") {
    // L = (0, 0, -10), b = -20, c = 75, discriminant = 100, t = 5 or 15
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("A ray through the side of the sphere hits it", "[sphere]") {
    // L = (-3, 0, -10), b = -20, c = 84, discriminant = 64, t = 6 or 14
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, Colour(1, 0, 0));

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("A ray beside the sphere misses it", "[sphere]") {
    // L = (-6, 0, -10), b = -20, c = 111, discriminant = -44
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("A sphere behind the eye is not hit", "[sphere]") {
    // L = (0, 0, 10), b = 20, c = 75, discriminant = 100, t = -5 or -15
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, Colour(1, 0, 0));

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("A sphere keeps its colour", "[sphere]") {
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0.5, 0));

    REQUIRE_THAT(sphere.colour().r(), WithinAbs(1, tolerance));
    REQUIRE_THAT(sphere.colour().g(), WithinAbs(0.5, tolerance));
    REQUIRE_THAT(sphere.colour().b(), WithinAbs(0, tolerance));
}
