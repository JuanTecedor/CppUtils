unsigned int fact(unsigned int number) {
    return number <= 1 ? number : fact(number - 1) * number;
}

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Factorials", "[factorial]") {
    REQUIRE(fact(1) == 1);
    REQUIRE(fact(2) == 2);
    REQUIRE(fact(3) == 6);
    REQUIRE(fact(10) == 3'628'800);
}
