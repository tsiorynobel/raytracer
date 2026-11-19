#include <catch2/catch_test_macros.hpp>
#include "material/flat_shader.h"
#include "test_helpers.h"

TEST_CASE("A flat shader gives its colour", "[material]") {
    const FlatShader shader(Colour(1, 0.5, 0));
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    requireColoursEqual(shader.shade(ray), Colour(1, 0.5, 0));
}

TEST_CASE("A flat shader gives the same colour whatever the ray", "[material]") {
    const FlatShader shader(Colour(1, 0.5, 0));
    Ray ray(Vector(1, 2, 3), Vector(-3, 4, 0));

    requireColoursEqual(shader.shade(ray), Colour(1, 0.5, 0));
}
