#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "render/trace.h"
#include "geometry/sphere.h"
#include "material/lambert_shader.h"
#include "test_helpers.h"

// Ray from (0, 0, -1) along (0, 0, 1), a scene with one red Lambert sphere of radius 5.

TEST_CASE("A ray that hits the sphere facing the sun is fully lit", "[trace]") {
    // Hit (0, 0, 4), N = (0, 0, -1), L = (0, 0, -1): N . L = 1
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    const LambertShader red(Colour(1, 0, 0));
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(1, 0, 0));
}

TEST_CASE("A sun at an angle shades the sphere", "[trace]") {
    // N = (0, 0, -1), L = (0.6, 0, -0.8): N . L = 0.8
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    const LambertShader red(Colour(1, 0, 0));
    Scene scene(Vector(0.6, 0, -0.8));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(0.8, 0, 0));
}

TEST_CASE("A ray that hits the side of the sphere is shaded by its normal", "[trace]") {
    // Hit (0, 0, 5), N = (-0.6, 0, -0.8), L = (0, 0, -1): N . L = 0.8
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    const LambertShader red(Colour(1, 0, 0));
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(3, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(0.8, 0, 0));
}

TEST_CASE("A ray that misses the sphere is black", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    const LambertShader red(Colour(1, 0, 0));
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(0, 0, 0));
}
