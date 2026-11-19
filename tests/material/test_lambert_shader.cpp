#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include "material/lambert_shader.h"
#include "geometry/hit_info.h"
#include "light/light.h"
#include "test_helpers.h"

// Lambert: colour = surface colour * light colour * max(0, N . L),
// with N the unit normal and L the unit vector from the hit point to the light.

TEST_CASE("A Lambert surface facing the light gets its full colour", "[material]") {
    // N = (0, 1, 0), L = (0, 1, 0): N . L = 1
    const LambertShader shader(Colour(1, 0.5, 0.25));
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), shader};
    Light light(Vector(0, 10, 0), Colour(1, 1, 1));

    requireColoursEqual(shader.shade(hit, light), Colour(1, 0.5, 0.25));
}

TEST_CASE("A Lambert surface lit from the side is black", "[material]") {
    // N = (0, 1, 0), L = (1, 0, 0): N . L = 0
    const LambertShader shader(Colour(1, 0.5, 0.25));
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), shader};
    Light light(Vector(10, 0, 0), Colour(1, 1, 1));

    requireColoursEqual(shader.shade(hit, light), Colour(0, 0, 0));
}

TEST_CASE("A Lambert surface lit from behind is black, not negative", "[material]") {
    // N = (0, 1, 0), L = (0, -1, 0): N . L = -1, clamped to 0
    const LambertShader shader(Colour(1, 0.5, 0.25));
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), shader};
    Light light(Vector(0, -10, 0), Colour(1, 1, 1));

    requireColoursEqual(shader.shade(hit, light), Colour(0, 0, 0));
}

TEST_CASE("A Lambert surface gets darker as the light gets lower", "[material]") {
    // Hit point (0, 5, 0), light (0, 10, 10): point to light = (0, 5, 10), length sqrt(125)
    // N . L = 5 / sqrt(125) = 1 / sqrt(5)
    const LambertShader shader(Colour(1, 0.5, 0.25));
    HitInfo hit{Vector(0, 5, 0), Vector(0, 1, 0), shader};
    Light light(Vector(0, 10, 10), Colour(1, 1, 1));

    double k = 1 / std::sqrt(5.0);
    requireColoursEqual(shader.shade(hit, light), Colour(k, 0.5 * k, 0.25 * k));
}

TEST_CASE("A Lambert surface takes the colour of the light", "[material]") {
    // Facing the light: (1, 0.5, 0.25) * (0.5, 1, 0) = (0.5, 0.5, 0)
    const LambertShader shader(Colour(1, 0.5, 0.25));
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), shader};
    Light light(Vector(0, 10, 0), Colour(0.5, 1, 0));

    requireColoursEqual(shader.shade(hit, light), Colour(0.5, 0.5, 0));
}
