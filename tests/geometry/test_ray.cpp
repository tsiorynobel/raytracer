#include <catch2/catch_test_macros.hpp>
#include "geometry/ray.h"
#include "test_helpers.h"

TEST_CASE("A ray keeps its origin and its direction", "[ray]") {
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));

    requireVectorsEqual(ray.origin(), Vector(1, 2, 3));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}

TEST_CASE("A ray gives the point at distance t along it", "[ray]") {
    // (1, 2, 3) + 2 * (3, 4, 0) = (7, 10, 3)
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));

    requireVectorsEqual(ray.at(2), Vector(7, 10, 3));
}
