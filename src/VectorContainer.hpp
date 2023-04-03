#ifndef VECTOR_CONTAINER_HPP
#define VECTOR_CONTAINER_HPP

#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>

template<typename T, std::size_t SIZE> requires (SIZE > 0)
class VectorContainer {
public:
    using value_type = T;
    using reference = value_type &;
    using iterator = value_type *;
    using const_iterator = const value_type *;

    constexpr explicit VectorContainer() noexcept = default;

    constexpr explicit VectorContainer(const value_type & val) noexcept {
        m_data.fill(val);
    }

    template <typename... U>
    constexpr VectorContainer(U... ts) : m_data{ts...} {
    }

    constexpr VectorContainer(const VectorContainer<value_type, SIZE> &) noexcept = default;

    constexpr VectorContainer & operator=(const VectorContainer<value_type, SIZE> &) noexcept = default;

    constexpr VectorContainer & operator=(VectorContainer<value_type, SIZE> &&) noexcept = default;

    template<typename U>
    constexpr static VectorContainer fromCast(const VectorContainer<U, SIZE> & other) noexcept {
        VectorContainer<T, SIZE> result;
        std::transform(other.begin(), other.end(), result.begin(), [](const auto & element){
            return static_cast<U>(element);
        });
        return result;
    }

    template <typename U, typename S>
    [[nodiscard]] constexpr static VectorContainer<T, 2> fromAngleAndLength(const U & angle, const S & scalar) noexcept {
        return VectorContainer<T, 2>{
            static_cast<T>(std::cos(angle) * scalar),
            static_cast<T>(std::sin(angle) * scalar)
        };
    }

    // template <typename U = value_type>
    // [[nodiscard]] constexpr U lengthSquared() const noexcept;

    // template <typename U = value_type>
    // [[nodiscard]] constexpr U length() const noexcept;

    // [[nodiscard]] constexpr VectorContainer<T, SIZE> normalized() const noexcept;

    // template <typename PRECISION = float>
    // [[nodiscard]] constexpr PRECISION angle(const VectorContainer<T, SIZE> & other) const noexcept;

    // [[nodiscard]] constexpr VectorContainer<T, SIZE> reflect(const VectorContainer<T, SIZE> & normal) const noexcept;

    // [[nodiscard]] constexpr VectorContainer<T, SIZE> lerp(const VectorContainer<T, SIZE> & other, float percent) const noexcept;

    [[nodiscard]] constexpr const value_type & operator[](std::size_t i) const noexcept {
        return m_data[i];
    }

    [[nodiscard]] constexpr value_type & operator[](std::size_t i) noexcept {
        return m_data[i];
    }

    [[nodiscard]] constexpr VectorContainer<T, SIZE> operator+(const VectorContainer<T, SIZE> & rhs) const noexcept {
        VectorContainer<T, SIZE> result;
        std::transform(begin(), end(), rhs.begin(), result.begin(), std::plus<T>());
        return result;
    }

    [[nodiscard]] constexpr VectorContainer<T, SIZE> operator-(const VectorContainer<T, SIZE> & rhs) const noexcept {
        VectorContainer<T, SIZE> result;
        std::transform(begin(), end(), rhs.begin(), result.begin(), std::minus<T>());
        return result;
    }

    [[nodiscard]] constexpr VectorContainer<T, SIZE> operator-() const noexcept {
        VectorContainer<T, SIZE> result;
        std::transform(begin(), end(), result.begin(), std::negate<T>());
        return result;
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    [[nodiscard]] constexpr VectorContainer<T, SIZE> operator*(const U & scalar) const noexcept {
        VectorContainer<T, SIZE> result;
        std::transform(begin(), end(), result.begin(), [scalar](const auto & element){
            return element * scalar;
        });
        return result;
    }

    [[nodiscard]] constexpr T operator*(const VectorContainer<T, SIZE> & rhs) const noexcept {
        return std::inner_product(begin(), end(), rhs.begin(), T{});
    }

    template <typename U>
    [[nodiscard]] constexpr VectorContainer<T, SIZE> operator/(const U & scalar) const noexcept {
        VectorContainer<T, SIZE> result;
        std::transform(begin(), end(), result.begin(), [scalar](const auto & element){
            return element / scalar;
        });
        return result;
    }

    constexpr VectorContainer<T, SIZE> operator+=(const VectorContainer<T, SIZE> & rhs) noexcept {
        std::transform(begin(), end(), rhs.begin(), begin(), std::plus<T>());
        return *this;
    }

    constexpr VectorContainer<T, SIZE> operator-=(const VectorContainer<T, SIZE> & rhs) noexcept {
        std::transform(begin(), end(), rhs.begin(), begin(), std::minus<T>());
        return *this;
    }

    template <typename U>
    constexpr VectorContainer<T, SIZE> operator*=(const U & scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    template <typename U>
    constexpr VectorContainer<T, SIZE> operator/=(const U & scalar) noexcept {
        *this = *this / scalar;
        return *this;
    }

    [[nodiscard]] constexpr bool operator==(const VectorContainer<T, SIZE> & rhs) const noexcept {
        return m_data == rhs.m_data;
    }

    // template<typename U>
    // [[nodiscard]] constexpr bool equals(const VectorContainer<T, SIZE> & rhs, const U & epsilon) const noexcept;

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
protected:
    std::array<value_type, SIZE> m_data;
};

template <typename T, std::size_t SIZE>
constexpr VectorContainer<T, SIZE> operator*(const T & scalar, const VectorContainer<T, SIZE> & rhs) noexcept
{
    return rhs * scalar;
}

template <typename T, std::size_t SIZE>
constexpr VectorContainer<T, SIZE> operator/(const T & scalar, const VectorContainer<T, SIZE> & rhs) noexcept
{
    return scalar / rhs;
}

#endif // VECTOR_CONTAINER_HPP
