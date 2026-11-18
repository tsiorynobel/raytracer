#include <catch2/catch_test_macros.hpp>
#include "vector.h"

TEST_CASE("Adding two vectors adds each component", "[vector]") {
    Vector a(3, 4, 0);
    Vector b(4, -3, 0);

    Vector sum = a.add(b);

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 0);
}

TEST_CASE("Adding two vectors also adds the z component", "[vector]") {
    Vector a(3, 4, 1);
    Vector b(4, -3, 2);

    Vector sum = a.add(b);

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 3);
}
