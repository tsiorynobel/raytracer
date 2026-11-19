#include <catch2/catch_test_macros.hpp>
#include "material/flat_shader.h"
#include "test_helpers.h"

TEST_CASE("A flat shader gives its colour", "[material]") {
    const FlatShader shader(Colour(1, 0.5, 0));

    requireColoursEqual(shader.shade(Vector(0, 0, -1), Vector(0, 0, -1)), Colour(1, 0.5, 0));
}

TEST_CASE("A flat shader ignores the normal and the light", "[material]") {
    // The light is behind the surface: a flat shader does not care.
    const FlatShader shader(Colour(1, 0.5, 0));

    requireColoursEqual(shader.shade(Vector(0, 0, -1), Vector(0, 0, 1)), Colour(1, 0.5, 0));
}
