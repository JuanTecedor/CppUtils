#ifndef VECTOR_TUPLE_HPP
#define VECTOR_TUPLE_HPP

#include <array>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>

#include "VectorTupleHelpers.hpp"

template<typename T, std::size_t SIZE> requires (SIZE > 0)
class VectorTuple {
private:
    using tuple_type = typename TupleOfN<T, SIZE>::type;
    tuple_type m_data;
public:
    using value_type = T;
    using reference = value_type &;

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

    template <typename U, typename S>
    [[nodiscard]] consteval static VectorTuple fromAngleAndLength(const U & angle, const S & scalar) noexcept {
        return VectorTuple<T, 2>{
            static_cast<T>(std::cos(angle) * static_cast<U>(scalar)),
            static_cast<T>(std::sin(angle) * static_cast<U>(scalar))
        };
    }

    template <typename U = value_type>
    [[nodiscard]] constexpr U lengthSquared() const noexcept {
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

template <std::size_t SIZE>
using VectorTuplei = VectorTuple<int, SIZE>;

template <std::size_t SIZE>
using VectorTupleu = VectorTuple<unsigned int, SIZE>;

template <std::size_t SIZE>
using VectorTuplef = VectorTuple<float, SIZE>;

#endif // VECTOR_HPP
