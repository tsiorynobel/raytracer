#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

void requireVectorsEqual(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

void requireColoursEqual(const Colour& actual, const Colour& expected) {
    REQUIRE_THAT(actual.r(), WithinAbs(expected.r(), tolerance));
    REQUIRE_THAT(actual.g(), WithinAbs(expected.g(), tolerance));
    REQUIRE_THAT(actual.b(), WithinAbs(expected.b(), tolerance));
}
