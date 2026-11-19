#include <memory>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "scene/scene.h"
#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

namespace {
const FlatShader red(Colour(1, 0, 0));
const FlatShader blue(Colour(0, 0, 1));
}

// Ray from (0, 0, -1) along (0, 0, 1). The sphere at (0, 0, 9), radius 5, is hit at t = 5.
// A plane through (0, 0, z) with normal (0, 0, -1) is hit at t = z + 1.
// Each case adds the shapes in both orders: keeping the first hit found would pass one order only.

TEST_CASE("A plane in front of the sphere gives the nearest hit", "[scene]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    bool sphereFirst = GENERATE(true, false);
    Scene scene(Vector(0, 0, -1));
    std::unique_ptr<Shape> sphere = std::make_unique<Sphere>(Vector(0, 0, 9), 5, red);
    std::unique_ptr<Shape> plane = std::make_unique<Plane>(Vector(0, 0, 2), Vector(0, 0, -1), blue);
    if (sphereFirst) {
        scene.add(std::move(sphere));
        scene.add(std::move(plane));
    } else {
        scene.add(std::move(plane));
        scene.add(std::move(sphere));
    }

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3, tolerance));
    REQUIRE(&hit->material == &blue);
}

TEST_CASE("A plane behind the sphere leaves the sphere's hit", "[scene]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    bool sphereFirst = GENERATE(true, false);
    Scene scene(Vector(0, 0, -1));
    std::unique_ptr<Shape> sphere = std::make_unique<Sphere>(Vector(0, 0, 9), 5, red);
    std::unique_ptr<Shape> plane = std::make_unique<Plane>(Vector(0, 0, 20), Vector(0, 0, -1), blue);
    if (sphereFirst) {
        scene.add(std::move(sphere));
        scene.add(std::move(plane));
    } else {
        scene.add(std::move(plane));
        scene.add(std::move(sphere));
    }

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    REQUIRE(&hit->material == &red);
}

TEST_CASE("A ray that misses every shape hits nothing", "[scene]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, red));

    REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}

TEST_CASE("An empty scene hits nothing", "[scene]") {
    Scene scene(Vector(0, 0, -1));

    REQUIRE_FALSE(scene.nearestHit(Ray(Vector(0, 0, -1), Vector(0, 0, 1))).has_value());
}

TEST_CASE("The scene keeps the direction to the sun as a unit vector", "[scene]") {
    // (0, 3, -4) has length 5: (0, 0.6, -0.8)
    Scene scene(Vector(0, 3, -4));

    requireVectorsEqual(scene.toLight(), Vector(0, 0.6, -0.8));
}
