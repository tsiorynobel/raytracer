#include <catch2/catch_test_macros.hpp>
#include "material/lambert_shader.h"
#include "test_helpers.h"

// Lambert's law: colour = max(0, N . L) * surface colour, N and L unit vectors.
// An orange surface (1, 0.5, 0) facing the eye: N = (0, 0, -1).

TEST_CASE("A Lambert surface facing the sun gets its full colour", "[material]") {
    // L = (0, 0, -1): N . L = 1
    const LambertShader orange(Colour(1, 0.5, 0));

    requireColoursEqual(orange.shade(Vector(0, 0, -1), Vector(0, 0, -1)), Colour(1, 0.5, 0));
}

TEST_CASE("A Lambert surface lit at an angle is darker", "[material]") {
    // L = (0.6, 0, -0.8): N . L = 0.8, colour (0.8, 0.4, 0)
    const LambertShader orange(Colour(1, 0.5, 0));

    requireColoursEqual(orange.shade(Vector(0, 0, -1), Vector(0.6, 0, -0.8)), Colour(0.8, 0.4, 0));
}

TEST_CASE("A Lambert surface lit from the side is black", "[material]") {
    // L = (1, 0, 0): N . L = 0
    const LambertShader orange(Colour(1, 0.5, 0));

    requireColoursEqual(orange.shade(Vector(0, 0, -1), Vector(1, 0, 0)), Colour(0, 0, 0));
}

TEST_CASE("A Lambert surface facing away from the sun is black, not negative", "[material]") {
    // L = (0, 0, 1): N . L = -1, clamped to 0
    const LambertShader orange(Colour(1, 0.5, 0));

    requireColoursEqual(orange.shade(Vector(0, 0, -1), Vector(0, 0, 1)), Colour(0, 0, 0));
}
