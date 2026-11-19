#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "colour/colour.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("A colour keeps its red, green and blue parts", "[colour]") {
    Colour colour(1, 0.5, 0);

    REQUIRE_THAT(colour.r(), WithinAbs(1, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0.5, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0, tolerance));
}

TEST_CASE("A colour times a number scales each part", "[colour]") {
    // (1, 0.5, 0.25) * 0.5 = (0.5, 0.25, 0.125)
    requireColoursEqual(Colour(1, 0.5, 0.25) * 0.5, Colour(0.5, 0.25, 0.125));
}

TEST_CASE("A colour times a colour multiplies part by part", "[colour]") {
    // A yellow-orange surface under a green-yellow light:
    // (1 * 0.5, 0.5 * 1, 0.25 * 0) = (0.5, 0.5, 0)
    requireColoursEqual(Colour(1, 0.5, 0.25) * Colour(0.5, 1, 0), Colour(0.5, 0.5, 0));
}
