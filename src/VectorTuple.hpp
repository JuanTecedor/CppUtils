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
consteval auto makeTupleFromParameters(Ts&&... args) {
    return std::make_tuple(std::forward<Ts>(args)...);
}

template <typename Tuple1, typename Tuple2, std::size_t... Indices, typename BinaryOp>
constexpr auto tupleElementWiseOpHelper(const Tuple1& t1, const Tuple2& t2, std::index_sequence<Indices...>, BinaryOp op) {
    return std::make_tuple(op(std::get<Indices>(t1), std::get<Indices>(t2))...);
}

template <typename Tuple1, typename Tuple2, typename BinaryOp>
constexpr auto tupleElementWiseOp(const Tuple1& t1, const Tuple2& t2, BinaryOp op) {
    return tupleElementWiseOpHelper(t1, t2, std::make_index_sequence<std::tuple_size_v<Tuple1>>(), op);
}

template <typename TUPLE, std::size_t... Indices, typename BinaryOp, typename T>
constexpr auto tupleBinaryOpHelper(const TUPLE& tuple, std::index_sequence<Indices...>, BinaryOp op, const T & scalar) {
    return std::make_tuple(op(std::get<Indices>(tuple), scalar)...);
}

template <typename TUPLE, typename BinaryOp, typename T>
constexpr TUPLE tupleBinaryOp(const TUPLE& tuple, BinaryOp op, const T & scalar) {
    return tupleBinaryOpHelper(tuple, std::make_index_sequence<std::tuple_size_v<TUPLE>>(), op, scalar);
}

template <typename TUPLE, std::size_t... Indices, typename UnaryOp>
constexpr auto tupleUnaryOpHelper(const TUPLE& tuple, std::index_sequence<Indices...>, UnaryOp op) {
    return std::make_tuple(op(std::get<Indices>(tuple))...);
}

template <typename TUPLE, typename UnaryOp>
constexpr TUPLE tupleUnaryOp(const TUPLE& tuple, UnaryOp op) {
    return tupleUnaryOpHelper(tuple, std::make_index_sequence<std::tuple_size_v<TUPLE>>(), op);
}

template <std::size_t Index, typename Tuple1, typename Tuple2>
std::enable_if_t<Index == 0, decltype(std::get<0>(std::declval<Tuple1>()) * std::get<0>(std::declval<Tuple2>()))>
tupleDotProductHelper(const Tuple1&, const Tuple2&) {
    return decltype(std::get<0>(std::declval<Tuple1>()) * std::get<0>(std::declval<Tuple2>()))(0);
}

template <std::size_t Index, typename Tuple1, typename Tuple2>
std::enable_if_t<Index != 0, decltype(std::get<0>(std::declval<Tuple1>()) * std::get<0>(std::declval<Tuple2>()))>
tupleDotProductHelper(const Tuple1& t1, const Tuple2& t2) {
    auto tail = tupleDotProductHelper<Index - 1>(t1, t2);
    auto product = std::get<Index - 1>(t1) * std::get<Index - 1>(t2);
    return tail + product;
}

template <typename... Args1, typename... Args2>
auto tupleDotProduct(const std::tuple<Args1...>& t1, const std::tuple<Args2...>& t2) {
    static_assert(sizeof...(Args1) == sizeof...(Args2), "Tuples must have the same size.");
    return tupleDotProductHelper<sizeof...(Args1)>(t1, t2);
}

template<typename T, std::size_t SIZE> requires (SIZE > 0)
class VectorTuple {
private:
    using tuple_type = typename TupleOfN<T, SIZE>::type;
    tuple_type m_data;
public:
    using value_type = T;
    using reference = value_type &;
    using iterator = value_type *;
    using const_iterator = const value_type *;

    template <typename... ARGS, typename = std::enable_if_t<std::conjunction_v<std::is_same<T, std::decay_t<ARGS>>...>>>
    consteval VectorTuple(ARGS&&... args) : m_data(std::forward<ARGS>(args)...) {}

    template <T VALUE>
    [[nodiscard]] consteval static VectorTuple from_val() noexcept {
        VectorTuple<T, SIZE> ret;
        ret.m_data = createTupleWithSameValue<T, SIZE>(VALUE);
        return ret;
    }

    template <typename U>
    [[nodiscard]] constexpr VectorTuple(const VectorTuple<U, SIZE> & other) noexcept : m_data{other.m_data} { }

    template <typename U, std::size_t S>
    friend class VectorTuple;

    // constexpr VectorTuple(const VectorTuple<value_type, SIZE> &) noexcept = default;

    // constexpr VectorTuple & operator=(const VectorTuple<value_type, SIZE> &) noexcept = default;

    // constexpr VectorTuple & operator=(VectorTuple<value_type, SIZE> && other) noexcept = default;

    template <typename U, typename S>
    [[nodiscard]] consteval static VectorTuple fromAngleAndLength(const U & angle, const S & scalar) noexcept {
        return VectorTuple<T, 2>{
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

    [[nodiscard]] constexpr VectorTuple<T, SIZE> normalized() const noexcept {
        VectorTuple<T, SIZE> result = *this;
        result.normalize();
        return result;
    }

    template <typename PRECISION = float>
    [[nodiscard]] constexpr PRECISION angle(const VectorTuple<T, SIZE> & other) const noexcept {
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

    [[nodiscard]] constexpr VectorTuple<T, SIZE> operator+(const VectorTuple<T, SIZE> & rhs) const noexcept {
        VectorTuple<T, SIZE> result;
        result.m_data = tupleElementWiseOp(m_data, rhs.m_data, std::plus());
        return result;
    }

    [[nodiscard]] constexpr VectorTuple<T, SIZE> operator-(const VectorTuple<T, SIZE> & rhs) const noexcept {
        VectorTuple<T, SIZE> result;
        result.m_data = tupleElementWiseOp(m_data, rhs.m_data, std::minus());
        return result;
    }

    [[nodiscard]] constexpr VectorTuple<T, SIZE> operator-() const noexcept {
        VectorTuple<T, SIZE> result;
        result.m_data = tupleUnaryOp(m_data, std::negate<>());
        return result;
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    [[nodiscard]] constexpr VectorTuple<T, SIZE> operator*(const U & scalar) const noexcept {
        VectorTuple<T, SIZE> result;
        result.m_data = tupleBinaryOp(m_data, std::multiplies<>(), scalar);
        return result;
    }

    [[nodiscard]] constexpr T operator*(const VectorTuple<T, SIZE> & rhs) const noexcept {
        return tupleDotProduct(m_data, rhs.m_data);
    }

    template <typename U>
    [[nodiscard]] constexpr VectorTuple<T, SIZE> operator/(const U & scalar) const noexcept {
        VectorTuple<T, SIZE> result;
        result.m_data = tupleBinaryOp(m_data, std::divides<>(), scalar);
        return result;
    }

    constexpr VectorTuple<T, SIZE> operator+=(const VectorTuple<T, SIZE> & rhs) noexcept {
        m_data = tupleElementWiseOp(m_data, rhs.m_data, std::plus());
        return *this;
    }

    constexpr VectorTuple<T, SIZE> operator-=(const VectorTuple<T, SIZE> & rhs) noexcept {
        m_data = tupleElementWiseOp(m_data, rhs.m_data, std::minus());
        return *this;
    }

    template <typename U>
    constexpr VectorTuple<T, SIZE> operator*=(const U & scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    template <typename U>
    constexpr VectorTuple<T, SIZE> operator/=(const U & scalar) noexcept {
        *this = *this / scalar;
        return *this;
    }

    [[nodiscard]] constexpr auto operator<=>(const VectorTuple<T, SIZE>&) const = default;
};

template <typename T, std::size_t SIZE>
constexpr VectorTuple<T, SIZE> operator*(const T & scalar, const VectorTuple<T, SIZE> & rhs) noexcept
{
    return rhs * scalar;
}

template <typename T, std::size_t SIZE>
constexpr VectorTuple<T, SIZE> operator/(const T & scalar, const VectorTuple<T, SIZE> & rhs) noexcept
{
    return scalar / rhs;
}

template <typename T>
using VectorTuple2 = VectorTuple<T, 2>;

template <typename T>
using VectorTuple3 = VectorTuple<T, 3>;

using VectorTuple2i = VectorTuple2<int>;
using VectorTuple2u = VectorTuple2<unsigned int>;
using VectorTuple2f = VectorTuple2<float>;

using VectorTuple3i = VectorTuple3<int>;
using VectorTuple3u = VectorTuple3<unsigned int>;
using VectorTuple3f = VectorTuple3<float>;

#endif // VECTOR_HPP
