#ifndef VECTOR_TUPLE_HELPERS_HPP
#define VERTOR_TUPLE_HELPERS_HPP

#include <tuple>

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

#endif
