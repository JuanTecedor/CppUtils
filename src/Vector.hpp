#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "VectorContainer.hpp"

template<typename T, std::size_t N>
class Vector : public VectorContainer<T, N> {
public:
    using VectorContainer<T, N>::VectorContainer;
    [[no_unique_address]] T & x = this->m_data[0];
};

template<typename T>
class Vector<T, 2> : public VectorContainer<T, 2> {
public:
    using VectorContainer<T, 2>::VectorContainer;
    [[no_unique_address]] T & x = this->m_data[0];
    [[no_unique_address]] T & y = this->m_data[1];
};

template<typename T>
class Vector<T, 3> : public VectorContainer<T, 3> {
public:
    using VectorContainer<T, 3>::VectorContainer;
    [[no_unique_address]] T & x = this->m_data[0];
    [[no_unique_address]] T & y = this->m_data[1];
    [[no_unique_address]] T & z = this->m_data[2];
};

using Vector2i = Vector<int, 2>;
using Vector2u = Vector<unsigned int, 2>;
using Vector2f = Vector<float, 2>;

using Vector3i = Vector<int, 3>;
using Vector3u = Vector<unsigned int, 3>;
using Vector3f = Vector<float, 3>;

#endif // VECTOR_HPP
