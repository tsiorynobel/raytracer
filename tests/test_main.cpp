#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

TEST_CASE("Sanity check", "[smoke]") {
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("Floating point equality", "[smoke]") {
    float a = 0.1f + 0.2f;
    REQUIRE(a == Catch::Approx(0.3f).epsilon(1e-5));
}
