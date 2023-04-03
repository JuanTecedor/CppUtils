#include <type_traits>
#include <numbers>

#include <catch2/catch_test_macros.hpp>

#include "../src/Vector.hpp"

TEST_CASE("Test Vector Constructors") {
    Vector2i v2{2, 3};

    REQUIRE(Vector2i() == Vector2i{0, 0});
    REQUIRE(Vector2i{1} == Vector2i{1, 1});
    REQUIRE(Vector2i(4) == Vector2i{4, 4});
    REQUIRE(Vector2i{v2} == v2);
    REQUIRE(Vector2f::fromCast(v2) == Vector2f{2.f, 3.f});
    REQUIRE(Vector2i::fromAngleAndLength(0, 1) == Vector2i{1, 0});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float>, 1) == Vector2i{-1, 0});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float> / 2, 1) == Vector2i{0, 1});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float> * (3.f / 2), 1) == Vector2i{0, -1});
}
