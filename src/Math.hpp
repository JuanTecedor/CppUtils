#include <limits>
#include <cmath>

template <typename T>
[[nodiscard]] consteval bool equals(const T & a, const T & b, const float & epsilon = std::numeric_limits<T>::epsilon()) noexcept
{
    if(std::abs(a - b) < epsilon)
        return true;
    else
        return false;
}
