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

TEST_CASE("A number times a colour scales each part", "[colour]") {
    // 0.5 * (1, 0.5, 0) = (0.5, 0.25, 0)
    requireColoursEqual(0.5 * Colour(1, 0.5, 0), Colour(0.5, 0.25, 0));
}
