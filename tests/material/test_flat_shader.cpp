#include <catch2/catch_test_macros.hpp>
#include "material/flat_shader.h"
#include "geometry/hit_info.h"
#include "light/light.h"
#include "test_helpers.h"

TEST_CASE("A flat shader gives its colour", "[material]") {
    const FlatShader shader(Colour(1, 0.5, 0));
    HitInfo hit{Vector(0, 0, 0), Vector(0, 1, 0), shader};
    Light light(Vector(0, 10, 0), Colour(1, 1, 1));

    requireColoursEqual(shader.shade(hit, light), Colour(1, 0.5, 0));
}

TEST_CASE("A flat shader ignores the hit and the light", "[material]") {
    // The light is below the surface and red: a flat shader does not care.
    const FlatShader shader(Colour(1, 0.5, 0));
    HitInfo hit{Vector(1, 2, 3), Vector(0, 1, 0), shader};
    Light light(Vector(1, -10, 3), Colour(1, 0, 0));

    requireColoursEqual(shader.shade(hit, light), Colour(1, 0.5, 0));
}
