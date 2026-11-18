#include <catch2/catch_test_macros.hpp>
#include "vector.h"

TEST_CASE("Adding two vectors adds each component", "[vector]") {
    Vector sum = Vector(3, 4, 0) + Vector(4, -3, 0);

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 0);
}

TEST_CASE("Adding two vectors also adds the z component", "[vector]") {
    Vector sum = Vector(3, 4, 1) + Vector(4, -3, 2);

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 3);
}

TEST_CASE("Subtracting two vectors subtracts each component", "[vector]") {
    Vector difference = Vector(4, 5, 0) - Vector(1, 1, 0);

    REQUIRE(difference.x() == 3);
    REQUIRE(difference.y() == 4);
    REQUIRE(difference.z() == 0);
}

TEST_CASE("Subtracting two vectors also subtracts the z component", "[vector]") {
    Vector difference = Vector(4, 5, 6) - Vector(1, 1, 2);

    REQUIRE(difference.x() == 3);
    REQUIRE(difference.y() == 4);
    REQUIRE(difference.z() == 4);
}

TEST_CASE("Scaling a vector multiplies each component", "[vector]") {
    Vector scaled = 2.0 * Vector(3, -4, 1);

    REQUIRE(scaled.x() == 6);
    REQUIRE(scaled.y() == -8);
    REQUIRE(scaled.z() == 2);
}

TEST_CASE("The ray equation O + t * D gives the point at t", "[vector]") {
    Vector O(0, 8, 0);
    Vector D(3, -4, 0);
    double t = 2.0;

    Vector point = O + t * D;

    REQUIRE(point.x() == 6);
    REQUIRE(point.y() == 0);
    REQUIRE(point.z() == 0);
}

TEST_CASE("The dot product sums the products of the components", "[vector]") {
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, 3, 0)) == 24);
    REQUIRE(Vector(3, 4, 12).dot(Vector(4, 3, 1)) == 36);
}

TEST_CASE("The dot product of perpendicular vectors is zero", "[vector]") {
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, -3, 0)) == 0);
}

TEST_CASE("The length of a vector uses all three components", "[vector]") {
    REQUIRE(Vector(3, -4, 0).length() == 5);
    REQUIRE(Vector(3, 4, 12).length() == 13);
}
