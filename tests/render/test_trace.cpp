#include <catch2/catch_test_macros.hpp>
#include "render/trace.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

TEST_CASE("A ray that hits the sphere takes the colour its material gives", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    const FlatShader orange(Colour(1, 0.5, 0));
    Sphere sphere(Vector(0, 0, 9), 5, orange);

    Colour pixel = trace(ray, sphere);

    requireColoursEqual(pixel, Colour(1, 0.5, 0));
}

TEST_CASE("A ray that misses the sphere is black", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    const FlatShader red(Colour(1, 0, 0));
    Sphere sphere(Vector(6, 0, 9), 5, red);

    Colour pixel = trace(ray, sphere);

    requireColoursEqual(pixel, Colour(0, 0, 0));
}
