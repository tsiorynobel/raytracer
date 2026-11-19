#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

namespace {
const FlatShader red(Colour(1, 0, 0));
}

// Expected values from L = O - C, a = D.D, b = 2 D.L, c = L.L - r^2,
// discriminant = b^2 - 4ac, t = (-b +- sqrt(discriminant)) / 2a.
// The hit is the nearest t > 0; point = O + t D, normal = (point - C) / r.

TEST_CASE("A ray through the centre of the sphere hits its near side", "[sphere]") {
    // L = (0, 0, -10), b = -20, c = 75, discriminant = 100, t = 5 or 15
    // point = (0, 0, -1) + 5 (0, 0, 1) = (0, 0, 4), normal = (0, 0, -5) / 5
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
}

TEST_CASE("A ray through the side of the sphere gets the normal there", "[sphere]") {
    // L = (-3, 0, -10), b = -20, c = 84, discriminant = 64, t = 6 or 14
    // point = (0, 0, 5), normal = ((0, 0, 5) - (3, 0, 9)) / 5 = (-0.6, 0, -0.8)
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(6, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 5));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0, -0.8));
}

TEST_CASE("A ray that is not a unit vector hits the same point", "[sphere]") {
    // D = (0, 0, 2): a = 4, b = -40, c = 75, discriminant = 400, t = 2.5 or 7.5
    // point = (0, 0, -1) + 2.5 (0, 0, 2) = (0, 0, 4)
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 2));
    Sphere sphere(Vector(0, 0, 9), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2.5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
}

TEST_CASE("A ray from inside the sphere hits its far side", "[sphere]") {
    // Centre (0, 0, 1): L = (0, 0, -2), b = -4, c = -21, discriminant = 100, t = -3 or 7.
    // -3 is behind the eye; point = (0, 0, -1) + 7 (0, 0, 1) = (0, 0, 6), normal = (0, 0, 5) / 5
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 1), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(7, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 6));
    requireVectorsEqual(hit->normal, Vector(0, 0, 1));
}

TEST_CASE("A ray beside the sphere misses it", "[sphere]") {
    // L = (-6, 0, -10), b = -20, c = 111, discriminant = -44
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, red);

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("A sphere behind the eye is not hit", "[sphere]") {
    // L = (0, 0, 10), b = 20, c = 75, discriminant = 100, t = -5 or -15
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, red);

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("A sphere keeps the material it was given", "[sphere]") {
    const FlatShader orange(Colour(1, 0.5, 0));
    Sphere sphere(Vector(0, 0, 9), 5, orange);

    REQUIRE(&sphere.material() == &orange);
}

TEST_CASE("A hit carries the material of the sphere", "[sphere]") {
    const FlatShader orange(Colour(1, 0.5, 0));
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, orange);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(&hit->material == &orange);
}
