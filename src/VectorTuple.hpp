#ifndef VECTOR_TUPLE_HPP
#define VECTOR_TUPLE_HPP

#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <iostream> // TODO remove

template <typename T, std::size_t N>
struct TupleOfN {
    using type = decltype(std::tuple_cat(std::declval<std::tuple<T>>(), std::declval<typename TupleOfN<T, N - 1>::type>()));
};

template <typename T>
struct TupleOfN<T, 0> {
    using type = std::tuple<>;
};

template <typename T, std::size_t... Is>
consteval auto fillTupleWithValue(const T& value, std::index_sequence<Is...>) {
    return std::make_tuple((static_cast<void>(Is), value)...);
}

template <typename T, std::size_t N>
consteval auto createTupleWithSameValue(const T& value) {
    return fillTupleWithValue(value, std::make_index_sequence<N>());
}

template <typename... Ts>
auto makeTupleFromParameters(Ts&&... args) {
    return std::make_tuple(std::forward<Ts>(args)...);
}

template <typename Tuple1, typename Tuple2, std::size_t... Indices, typename BinaryOp>
auto tupleElementWiseOpHelper(const Tuple1& t1, const Tuple2& t2, std::index_sequence<Indices...>, BinaryOp op) {
    return std::make_tuple(op(std::get<Indices>(t1), std::get<Indices>(t2))...);
}

// Function to perform element-wise operation on tuples
template <typename Tuple1, typename Tuple2, typename BinaryOp>
auto tupleElementWiseOp(const Tuple1& t1, const Tuple2& t2, BinaryOp op) {
    return tupleElementWiseOpHelper(t1, t2, std::make_index_sequence<std::tuple_size_v<Tuple1>>(), op);
}

template<typename T, std::size_t SIZE> requires (SIZE > 0)
class Vector {
private:
    using tuple_type = typename TupleOfN<T, SIZE>::type;
    tuple_type m_data;
public:
    using value_type = T;
    using reference = value_type &;
    using iterator = value_type *;
    using const_iterator = const value_type *;

    template <typename... ARGS, typename = std::enable_if_t<std::conjunction_v<std::is_same<T, std::decay_t<ARGS>>...>>>
    consteval Vector(ARGS&&... args) : m_data(std::forward<ARGS>(args)...) {}

    template <T VALUE>
    [[nodiscard]] consteval static Vector from_val() noexcept {
        Vector<T, SIZE> ret;
        ret.m_data = createTupleWithSameValue<T, SIZE>(VALUE);
        return ret;
    }

    template <typename U>
    [[nodiscard]] constexpr Vector(const Vector<U, SIZE> & other) noexcept : m_data{other.m_data} { }

    template <typename U, std::size_t S>
    friend class Vector;

    // constexpr Vector(const Vector<value_type, SIZE> &) noexcept = default;

    // constexpr Vector & operator=(const Vector<value_type, SIZE> &) noexcept = default;

    // constexpr Vector & operator=(Vector<value_type, SIZE> && other) noexcept = default;

    template <typename U, typename S>
    [[nodiscard]] consteval static Vector fromAngleAndLength(const U & angle, const S & scalar) noexcept {
        return Vector<T, 2>{
            static_cast<T>(std::cos(angle) * static_cast<U>(scalar)),
            static_cast<T>(std::sin(angle) * static_cast<U>(scalar))
        };
    }

    template <typename U = value_type>
    [[nodiscard]] constexpr U lengthSquared() const noexcept {
        // return std::inner_product(begin(), end(), begin(), T{});
        return std::apply([](const auto & ... args){
            return ((args * args) + ...);
        }, m_data);
    }

    template <typename U = value_type>
    [[nodiscard]] constexpr U length() const noexcept {
        return static_cast<U>(std::sqrt(lengthSquared()));
    }

    constexpr bool is_null() const noexcept {
        return std::apply([](const auto&... args){
            return ((args == 0) && ...);
        }, m_data);
    }

    constexpr void normalize() noexcept {
        if(!is_null())
        {
            *this /= length();
        }
    }

    [[nodiscard]] constexpr Vector<T, SIZE> normalized() const noexcept {
        Vector<T, SIZE> result = *this;
        result.normalize();
        return result;
    }

    template <typename PRECISION = float>
    [[nodiscard]] constexpr PRECISION angle(const Vector<T, SIZE> & other) const noexcept {
        auto dot = *this * other;
        return static_cast<PRECISION>(std::acos(dot / (length() * other.length())));
    }

    template <std::size_t IDX>
    [[nodiscard]] constexpr const value_type & get() const noexcept {
        static_assert(IDX < SIZE);
        return std::get<IDX>(m_data);
    }

    template <std::size_t IDX>
    [[nodiscard]] constexpr value_type & get() noexcept {
        static_assert(IDX < SIZE);
        return std::get<IDX>(m_data);
    }

    [[nodiscard]] constexpr Vector<T, SIZE> operator+(const Vector<T, SIZE> & rhs) const noexcept {
        Vector<T, SIZE> result;
        result.m_data = tupleElementWiseOp(m_data, rhs.m_data, std::plus());
        return result;
    }

    [[nodiscard]] constexpr Vector<T, SIZE> operator-(const Vector<T, SIZE> & rhs) const noexcept {
        Vector<T, SIZE> result;
        result.m_data = tupleElementWiseOp(m_data, rhs.m_data, std::minus());
        return result;
    }

    [[nodiscard]] constexpr Vector<T, SIZE> operator-() const noexcept {
        Vector<T, SIZE> result;
        // std::transform(begin(), end(), result.begin(), std::negate<T>());
        return result;
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    [[nodiscard]] constexpr Vector<T, SIZE> operator*(const U & scalar) const noexcept {
        Vector<T, SIZE> result;
        // std::transform(begin(), end(), result.begin(), [scalar](const auto & element){
        //     return element * scalar;
        // });
        return result;
    }

    [[nodiscard]] constexpr T operator*(const Vector<T, SIZE> & rhs) const noexcept {
        // return std::inner_product(begin(), end(), rhs.begin(), T{});
        return {};
    }

    template <typename U>
    [[nodiscard]] constexpr Vector<T, SIZE> operator/(const U & scalar) const noexcept {
        Vector<T, SIZE> result;
        // std::transform(begin(), end(), result.begin(), [scalar](const auto & element){
        //     return element / scalar;
        // });
        return result;
    }

    constexpr Vector<T, SIZE> operator+=(const Vector<T, SIZE> & rhs) noexcept {
        // std::transform(begin(), end(), rhs.begin(), begin(), std::plus<T>());
        return *this;
    }

    constexpr Vector<T, SIZE> operator-=(const Vector<T, SIZE> & rhs) noexcept {
        // std::transform(begin(), end(), rhs.begin(), begin(), std::minus<T>());
        return *this;
    }

    template <typename U>
    constexpr Vector<T, SIZE> operator*=(const U & scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    template <typename U>
    constexpr Vector<T, SIZE> operator/=(const U & scalar) noexcept {
        *this = *this / scalar;
        return *this;
    }

    [[nodiscard]] constexpr auto operator<=>(const Vector<T, SIZE>&) const = default;
};

template <typename T, std::size_t SIZE>
constexpr Vector<T, SIZE> operator*(const T & scalar, const Vector<T, SIZE> & rhs) noexcept
{
    return rhs * scalar;
}

template <typename T, std::size_t SIZE>
constexpr Vector<T, SIZE> operator/(const T & scalar, const Vector<T, SIZE> & rhs) noexcept
{
    return scalar / rhs;
}

template <typename T>
using Vector2 = Vector<T, 2>;

template <typename T>
using Vector3 = Vector<T, 3>;

using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;

using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;
using Vector3f = Vector3<float>;

#endif // VECTOR_HPP
