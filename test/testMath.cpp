#include <catch2/catch_test_macros.hpp>

#include "../src/Math.hpp"

TEST_CASE("Test Equals") {
    REQUIRE(equals(1.F, 1.F));
    REQUIRE(equals(1.F, 1.00000001F));
    REQUIRE(!equals(1.F, 1.0000001F));
}
