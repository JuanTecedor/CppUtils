#ifndef VECTOR_CONTAINER_HPP
#define VECTOR_CONTAINER_HPP

#include <array>
#include <cmath>
#include <cassert>

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
        VectorContainer<T, SIZE> v;
        for(std::size_t i = 0; i < SIZE; ++i)
        {
            v[i] = static_cast<T>(other[i]);
        }
        return v;
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

    // [[nodiscard]] constexpr VectorContainer<T, SIZE> operator+(const VectorContainer<T, SIZE> & rhs) const noexcept;

    // [[nodiscard]] constexpr VectorContainer<T, SIZE> operator-(const VectorContainer<T, SIZE> & rhs) const noexcept;

    // [[nodiscard]] constexpr VectorContainer<T, SIZE> operator-() const noexcept;

    // template <typename U>
    // [[nodiscard]] constexpr VectorContainer<T, SIZE> operator*(const U & scalar) const noexcept;

    // [[nodiscard]] constexpr T operator*(const VectorContainer<T, SIZE> & rhs) const noexcept;

    // template <typename U>
    // [[nodiscard]] constexpr VectorContainer<T, SIZE> operator/(const U & scalar) const noexcept;

    // constexpr VectorContainer<T, SIZE> operator+=(const VectorContainer<T, SIZE> & rhs) noexcept;

    // constexpr VectorContainer<T, SIZE> operator-=(const VectorContainer<T, SIZE> & rhs) noexcept;

    // template <typename U>
    // constexpr VectorContainer<T, SIZE> operator*=(const U & scalar) noexcept;

    // template <typename U>
    // constexpr VectorContainer<T, SIZE> operator/=(const U & scalar) noexcept;

    [[nodiscard]] constexpr bool operator==(const VectorContainer<T, SIZE> & rhs) const noexcept {
        return m_data == rhs.m_data;
    }

    template<typename U>
    [[nodiscard]] constexpr bool equals(const VectorContainer<T, SIZE> & rhs, const U & epsilon) const noexcept;

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
