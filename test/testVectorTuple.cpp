#include <type_traits>
#include <numbers>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "../src/VectorTuple.hpp"

TEST_CASE("Test VectorTuple Constructors") {
    // TODO Allof??
    // auto v1 = Vector<int, 100>();  // This is not possible to test 100% reliably
    // REQUIRE(v1 != Vector<int, 100>::from_val<0>());

    Vector2i v2{2, 3};
    auto v3 = v2;
    REQUIRE(v3 == v2);

    auto v2i = Vector2i();
    REQUIRE(v2i == Vector2i{0, 0});
    REQUIRE(Vector2i{} == Vector2i{0, 0});
    REQUIRE(Vector2i::from_val<1>() == Vector2i{1, 1});
    REQUIRE(Vector2i::from_val<4>() == Vector2i{4, 4});

    auto v2f = Vector2f(v2);
    REQUIRE(v2f == Vector2f{2.f, 3.f});
    REQUIRE(Vector2i::fromAngleAndLength(0, 1) == Vector2i{1, 0});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float>, 1) == Vector2i{-1, 0});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float> / 2, 1) == Vector2i{0, 1});
    REQUIRE(Vector2i::fromAngleAndLength(std::numbers::pi_v<float> * (3.f / 2), 1) == Vector2i{0, -1});
}

TEST_CASE("Test VectorTuple Boolean Operators") {
    Vector2i v1{1, 2};
    Vector2i v2{1, 2};
    Vector2i v3{1, 3};

    REQUIRE(v1 == v2);
    REQUIRE(!(v3 == v1));
    REQUIRE(v3 != v1);
}

TEST_CASE("Test VectorTuple Binary Operators") {
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

// TEST_CASE("Test VectorTuple Dot Product") {
//     Vector2i v1{1, -7};
//     Vector2i v2{-9, 13};
//     REQUIRE((v1 * v2) == -100);
//     REQUIRE((v1 * v2) == (v2 * v1));
// }

// TEST_CASE("Test VectorTuple Unary Operators") {
//     REQUIRE(-Vector2i{1, -2} == Vector2i{-1, 2});
// }

// TEST_CASE("Test VectorTuple Assignment Operators") {
//     Vector2i v1{1, -5};
//     Vector2i v2{-3, 7};

//     v1 -= v2;
//     REQUIRE(v1 == Vector2i{4, -12});
//     v2 += v1;
//     REQUIRE(v2 == Vector2i{1, -5});

//     Vector2i v3{2, -3};
//     v3 *= -2;
//     REQUIRE(v3 == Vector2i{-4, 6});

//     Vector2i v4{8, -10};
//     v4 /= -2;
//     REQUIRE(v4 == Vector2i{-4, 5});
// }

// TEST_CASE("Test VectorTuple Length Operations") {
//     using Catch::Matchers::WithinRel;
//     Vector2i v1{5, 1};
//     REQUIRE(v1.lengthSquared() == 26);
//     REQUIRE(v1.length() == 5);

//     Vector3i v2{5, 1, -6};
//     REQUIRE(v2.lengthSquared() == 62);
//     REQUIRE(v2.length() == 7);

//     Vector3f v3{10.f, -20.f, 30.f};
//     Vector3f normalized = v3.normalized();
//     REQUIRE_THAT(normalized.length(), WithinRel(1.f));
//     REQUIRE_THAT(normalized.get<0>(), WithinRel(0.2672612419124244f));
//     REQUIRE_THAT(normalized.get<1>(), WithinRel(-0.5345224838248488f));
//     REQUIRE_THAT(normalized.get<2>(), WithinRel(0.8017837257372731f));
// }

// TEST_CASE("Test VectorTuple Null Length") {
//     using Catch::Matchers::WithinRel;
//     Vector2i v1{0, 0};
//     REQUIRE(v1.normalized() == Vector2i{0, 0});

//     Vector2f v2{0.f, 0.f};
//     REQUIRE(v2.normalized() == Vector2f{0.f, 0.f});
// }

// TEST_CASE("Test VectorTuple Angle") {
//     using Catch::Matchers::WithinRel;
//     Vector3f v1{3.f, 0.f, -1.f};
//     Vector3f v2{6.f, 6.f, -1.f};
//     REQUIRE_THAT(v1.angle(v2), WithinRel(std::numbers::pi_v<float> / 4, .01f));
// }
