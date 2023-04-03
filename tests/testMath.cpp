#include <catch2/catch_test_macros.hpp>

#include "../src/Math.hpp"

TEST_CASE("Test Equals") {
    REQUIRE(equals(1.f, 1.f));
    REQUIRE(equals(1.f, 1.00000001f));
    REQUIRE(!equals(1.f, 1.0000001f));
}
