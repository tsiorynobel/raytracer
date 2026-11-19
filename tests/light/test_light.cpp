#include <catch2/catch_test_macros.hpp>
#include "light/light.h"
#include "test_helpers.h"

TEST_CASE("A light keeps its position and its colour", "[light]") {
    const Light light(Vector(1, 2, 3), Colour(0.8, 0.6, 0.4));

    requireVectorsEqual(light.position(), Vector(1, 2, 3));
    requireColoursEqual(light.colour(), Colour(0.8, 0.6, 0.4));
}
