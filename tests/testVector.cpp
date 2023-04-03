#include <type_traits>
#include <numbers>

#include <catch2/catch_test_macros.hpp>

#include "../src/Vector.hpp"

TEST_CASE("Test Vector Constructors") {
    // Vector<int, 100> v1;  // This is not possible to test 100% reliably
    // REQUIRE(v1 != Vector<int, 100>(0));

    Vector2i v2{2, 3};

    REQUIRE(Vector2i() == Vector2i{0, 0});
    REQUIRE(Vector2i{} == Vector2i{0, 0});
    REQUIRE(Vector2i{1} == Vector2i{1, 1});
    REQUIRE(Vector2i(4) == Vector2i{4, 4});
    REQUIRE(Vector2i{v2} == v2);
    REQUIRE(Vector2f::fromCast(v2) == Vector2f{2.f, 3.f});
    REQUIRE(Vector2i::fromAngleAndLength(0, 1) == Vector2i{1, 0});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float>, 1) == Vector2i{-1, 0});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float> / 2, 1) == Vector2i{0, 1});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float> * (3.f / 2), 1) == Vector2i{0, -1});
}

TEST_CASE("Test Vector Boolean Operators") {
    Vector2i v1{1, 2};
    Vector2i v2{1, 2};
    Vector2i v3{1, 3};

    REQUIRE(v1 == v2);
    REQUIRE(!(v3 == v1));
    REQUIRE(v3 != v1);
}

TEST_CASE("Test Vector Binary Operators") {
    Vector2i v1{1, 2};
    Vector2i v2{-3, 4};

    REQUIRE(v1 + v2 == Vector2i{-2, 6});
    REQUIRE(v1 + v2 == v2 + v1);
    REQUIRE(v1 - v2 == Vector2i{4, -2});
    REQUIRE(v2 - v1 == Vector2i{-4, 2});
    REQUIRE(v1 * 2 == Vector2i{2, 4});
    REQUIRE(v2 * 2 == Vector2i{-6, 8});
    REQUIRE(v2 * 2 == 2 * v2);
    REQUIRE(Vector2i{6, -2} / -2 == Vector2i{-3, 1});
}

TEST_CASE("Test Vector Dot Product") {
    Vector2i v1{1, -7};
    Vector2i v2{-9, 13};
    REQUIRE((v1 * v2) == -100);
    REQUIRE((v1 * v2) == (v2 * v1));
}

TEST_CASE("Test Vector Unary Operators") {
    REQUIRE(-Vector2i{1, -2} == Vector2i{-1, 2});
}

TEST_CASE("Test Vector Assignment Operators") {
    Vector2i v1{1, -5};
    Vector2i v2{-3, 7};

    v1 -= v2;
    REQUIRE(v1 == Vector2i{4, -12});
    v2 += v1;
    REQUIRE(v2 == Vector2i{1, -5});

    Vector2i v3{2, -3};
    v3 *= -2;
    REQUIRE(v3 == Vector2i{-4, 6});

    Vector2i v4{8, -10};
    v4 /= -2;
    REQUIRE(v4 == Vector2i{-4, 5});
}
