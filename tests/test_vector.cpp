#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "vector.h"

using Catch::Matchers::WithinAbs;

static const double tolerance = 1e-9;

static void requireVectorsEqual(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

TEST_CASE("Adding two vectors adds each component", "[vector]") {
    requireVectorsEqual(Vector(3, 4, 0) + Vector(4, -3, 0), Vector(7, 1, 0));
}

TEST_CASE("Adding two vectors also adds the z component", "[vector]") {
    requireVectorsEqual(Vector(3, 4, 1) + Vector(4, -3, 2), Vector(7, 1, 3));
}

TEST_CASE("Subtracting two vectors subtracts each component", "[vector]") {
    requireVectorsEqual(Vector(4, 5, 0) - Vector(1, 1, 0), Vector(3, 4, 0));
}

TEST_CASE("Subtracting two vectors also subtracts the z component", "[vector]") {
    requireVectorsEqual(Vector(4, 5, 6) - Vector(1, 1, 2), Vector(3, 4, 4));
}

TEST_CASE("Scaling a vector multiplies each component", "[vector]") {
    requireVectorsEqual(2.0 * Vector(3, -4, 1), Vector(6, -8, 2));
}

TEST_CASE("The ray equation O + t * D gives the point at t", "[vector]") {
    Vector O(0, 8, 0);
    Vector D(3, -4, 0);
    double t = 2.0;

    requireVectorsEqual(O + t * D, Vector(6, 0, 0));
}

TEST_CASE("The dot product sums the products of the components", "[vector]") {
    REQUIRE_THAT(Vector(3, 4, 0).dot(Vector(4, 3, 0)), WithinAbs(24, tolerance));
    REQUIRE_THAT(Vector(3, 4, 12).dot(Vector(4, 3, 1)), WithinAbs(36, tolerance));
}

TEST_CASE("The dot product of perpendicular vectors is zero", "[vector]") {
    REQUIRE_THAT(Vector(3, 4, 0).dot(Vector(4, -3, 0)), WithinAbs(0, tolerance));
}

TEST_CASE("The length of a vector uses all three components", "[vector]") {
    REQUIRE_THAT(Vector(3, -4, 0).length(), WithinAbs(5, tolerance));
    REQUIRE_THAT(Vector(3, 4, 12).length(), WithinAbs(13, tolerance));
}

TEST_CASE("Normalising keeps the direction and gives a length of one", "[vector]") {
    requireVectorsEqual(Vector(3, -4, 0).normalised(), Vector(0.6, -0.8, 0));
}

TEST_CASE("A normalised vector has a length of one", "[vector]") {
    REQUIRE_THAT(Vector(3, 4, 12).normalised().length(), WithinAbs(1, tolerance));
}
