#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>

template<typename T, std::size_t SIZE> requires (SIZE > 0)
class Vector {
public:
    using value_type = T;
    using reference = value_type &;
    using iterator = value_type *;
    using const_iterator = const value_type *;

    constexpr explicit Vector() noexcept = default;

    constexpr explicit Vector(const value_type & val) noexcept {
        m_data.fill(val);
    }

    template <typename... U>
    constexpr Vector(U... ts) : m_data{ts...} {
    }

    template <typename U>
    constexpr Vector(const Vector<U, SIZE> & other) noexcept {
        std::transform(other.begin(), other.end(), m_data.begin(), [](const auto & element){
            return static_cast<T>(element);
        });
    }

    constexpr Vector(const Vector<value_type, SIZE> &) noexcept = default;

    constexpr Vector & operator=(const Vector<value_type, SIZE> &) noexcept = default;

    constexpr Vector & operator=(Vector<value_type, SIZE> && other) noexcept = default;

    template <typename U, typename S>
    [[nodiscard]] constexpr static Vector<T, 2> fromAngleAndLength(const U & angle, const S & scalar) noexcept {
        return Vector<T, 2>{
            static_cast<T>(std::cos(angle) * static_cast<U>(scalar)),
            static_cast<T>(std::sin(angle) * static_cast<U>(scalar))
        };
    }

    template <typename U = value_type>
    [[nodiscard]] constexpr U lengthSquared() const noexcept {
        return std::inner_product(begin(), end(), begin(), T{});
    }

    template <typename U = value_type>
    [[nodiscard]] constexpr U length() const noexcept {
        return static_cast<U>(std::sqrt(lengthSquared()));
    }

    constexpr bool is_null() const noexcept {
        return std::all_of(m_data.begin(), m_data.end(), [](const auto & val){ return val == T{}; });
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

    [[nodiscard]] constexpr const value_type & operator[](std::size_t i) const noexcept {
        assert(i < SIZE);
        return m_data[i];
    }

    [[nodiscard]] constexpr value_type & operator[](std::size_t i) noexcept {
        assert(i < SIZE);
        return m_data[i];
    }

    [[nodiscard]] constexpr Vector<T, SIZE> operator+(const Vector<T, SIZE> & rhs) const noexcept {
        Vector<T, SIZE> result;
        std::transform(begin(), end(), rhs.begin(), result.begin(), std::plus<T>());
        return result;
    }

    [[nodiscard]] constexpr Vector<T, SIZE> operator-(const Vector<T, SIZE> & rhs) const noexcept {
        Vector<T, SIZE> result;
        std::transform(begin(), end(), rhs.begin(), result.begin(), std::minus<T>());
        return result;
    }

    [[nodiscard]] constexpr Vector<T, SIZE> operator-() const noexcept {
        Vector<T, SIZE> result;
        std::transform(begin(), end(), result.begin(), std::negate<T>());
        return result;
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    [[nodiscard]] constexpr Vector<T, SIZE> operator*(const U & scalar) const noexcept {
        Vector<T, SIZE> result;
        std::transform(begin(), end(), result.begin(), [scalar](const auto & element){
            return element * scalar;
        });
        return result;
    }

    [[nodiscard]] constexpr T operator*(const Vector<T, SIZE> & rhs) const noexcept {
        return std::inner_product(begin(), end(), rhs.begin(), T{});
    }

    template <typename U>
    [[nodiscard]] constexpr Vector<T, SIZE> operator/(const U & scalar) const noexcept {
        Vector<T, SIZE> result;
        std::transform(begin(), end(), result.begin(), [scalar](const auto & element){
            return element / scalar;
        });
        return result;
    }

    constexpr Vector<T, SIZE> operator+=(const Vector<T, SIZE> & rhs) noexcept {
        std::transform(begin(), end(), rhs.begin(), begin(), std::plus<T>());
        return *this;
    }

    constexpr Vector<T, SIZE> operator-=(const Vector<T, SIZE> & rhs) noexcept {
        std::transform(begin(), end(), rhs.begin(), begin(), std::minus<T>());
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

    [[nodiscard]] constexpr bool operator==(const Vector<T, SIZE> & rhs) const noexcept {
        return m_data == rhs.m_data;
    }

    iterator begin() noexcept {
        return m_data.begin();
    }

    const_iterator begin() const noexcept {
        return m_data.begin();
    }

    iterator end() noexcept {
        return m_data.end();
    }

    const_iterator end() const noexcept {
        return m_data.end();
    }

private:
    std::array<T, SIZE> m_data;
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
