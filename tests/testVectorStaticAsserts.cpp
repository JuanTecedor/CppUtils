#include "../src/Vector.hpp"

// SFINAE (Substitution Failure Is Not An Error)

template <typename T>
struct has_member_variable_x
{
    template <typename U>
    static auto test(auto) -> decltype(std::declval<U>().x, std::true_type());

    template <typename>
    static auto test(...) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
inline constexpr bool has_member_variable_x_v = has_member_variable_x<T>::value;

template <typename T>
struct has_member_variable_y
{
    template <typename U>
    static auto test(auto) -> decltype(std::declval<U>().y, std::true_type());

    template <typename>
    static auto test(...) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
inline constexpr bool has_member_variable_y_v = has_member_variable_y<T>::value;

template <typename T>
struct has_member_variable_z
{
    template <typename U>
    static auto test(auto) -> decltype(std::declval<U>().z, std::true_type());

    template <typename>
    static auto test(...) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
inline constexpr bool has_member_variable_z_v = has_member_variable_z<T>::value;

void testVector1() {
    using testType = Vector<int, 1>;
    static_assert(has_member_variable_x_v<testType>);
    static_assert(!has_member_variable_y_v<testType>);
    static_assert(!has_member_variable_z_v<testType>);
}

void testVector2() {
    using testType = Vector<int, 2>;
    static_assert(has_member_variable_x_v<testType>);
    static_assert(has_member_variable_y_v<testType>);
    static_assert(!has_member_variable_z_v<testType>);
}

void testVector3() {
    using testType = Vector<int, 3>;
    static_assert(has_member_variable_x_v<testType>);
    static_assert(has_member_variable_y_v<testType>);
    static_assert(has_member_variable_z_v<testType>);
}
