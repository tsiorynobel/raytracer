#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

namespace {
const FlatShader green(Colour(0, 1, 0));
}

// Expected values from t = n . (Q - O) / (n . D), with Q a point of the plane
// and n its unit normal. No hit when n . D = 0 (parallel) or t <= 0 (behind).

TEST_CASE("A ray going down hits the floor", "[plane]") {
    // n = (0, 1, 0), Q - O = (0, -8, 0): n . (Q - O) = -8, n . D = -4, t = 2
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    std::optional<Hit> hit = floor.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(6, 0, 0));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
    REQUIRE(&hit->material == &green);
}

TEST_CASE("A plane's normal is made a unit vector", "[plane]") {
    // The line 3x + 4y = 24: n = (3, 4, 0) / 5 = (0.6, 0.8, 0), Q - O = (16, 0, 0)
    // n . (Q - O) = 9.6, n . D = 0.6 * 4 + 0.8 * 3 = 4.8, t = 2, point (0, 6, 0)
    Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), green);
    Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));

    std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 6, 0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0));
}

TEST_CASE("A ray parallel to the floor, above it, misses it", "[plane]") {
    // n . D = 0
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);
    Ray ray(Vector(0, 8, 0), Vector(5, 0, 0));

    REQUIRE_FALSE(floor.hit(ray).has_value());
}

TEST_CASE("A ray parallel to the floor, below it, misses it", "[plane]") {
    // n . D = 0 and n . (Q - O) = 8: without the parallel check, t = 8 / 0 = +infinity
    // and t <= 0 would not catch it.
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);
    Ray ray(Vector(0, -8, 0), Vector(5, 0, 0));

    REQUIRE_FALSE(floor.hit(ray).has_value());
}

TEST_CASE("A floor behind the ray is not hit", "[plane]") {
    // n . (Q - O) = -8, n . D = 4, t = -2
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);
    Ray ray(Vector(0, 8, 0), Vector(3, 4, 0));

    REQUIRE_FALSE(floor.hit(ray).has_value());
}

TEST_CASE("A plane can be used as any shape", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);
    const Shape& shape = floor;

    REQUIRE(shape.hit(Ray(Vector(0, 8, 0), Vector(3, -4, 0))).has_value());
}
