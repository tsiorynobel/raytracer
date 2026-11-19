#include <catch2/catch_test_macros.hpp>
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

namespace {
const FlatShader red(Colour(1, 0, 0));
}

// Expected values from L = O - C, a = D.D, b = 2 D.L, c = L.L - r^2,
// discriminant = b^2 - 4ac, t = (-b +- sqrt(discriminant)) / 2a.

TEST_CASE("A ray through the centre of the sphere hits it", "[sphere]") {
    // L = (0, 0, -10), b = -20, c = 75, discriminant = 100, t = 5 or 15
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, red);

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("A ray through the side of the sphere hits it", "[sphere]") {
    // L = (-3, 0, -10), b = -20, c = 84, discriminant = 64, t = 6 or 14
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, red);

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("A ray beside the sphere misses it", "[sphere]") {
    // L = (-6, 0, -10), b = -20, c = 111, discriminant = -44
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, red);

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("A sphere behind the eye is not hit", "[sphere]") {
    // L = (0, 0, 10), b = 20, c = 75, discriminant = 100, t = -5 or -15
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, red);

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("A sphere keeps the material it was given", "[sphere]") {
    const FlatShader orange(Colour(1, 0.5, 0));
    Sphere sphere(Vector(0, 0, 9), 5, orange);

    REQUIRE(&sphere.material() == &orange);
}
