#ifndef SLOTMAP_HPP
#define SLOTMAP_HPP

#include <tuple>

#include "UnorderedMapSlotMap.hpp"

template <typename... MAPS>
class SlotMap {
    using tuple_type = std::tuple<MAPS...>;
    inline static tuple_type data = std::make_tuple(MAPS{}...);

public:
    template<typename T, std::size_t I = 0>
    [[nodiscard]] consteval static auto & get() noexcept
    {
        using slotmap_type = std::tuple_element_t<I, tuple_type>;
        using element_type = typename slotmap_type::value_type;

        if constexpr (std::is_same_v<T, element_type>)
        {

            return std::get<I>(data);
        }
        else if constexpr(I + 1 != std::tuple_size_v<tuple_type>)
        {
            return get<T, I + 1>();
        }
        else
        {
            static_assert(I == 0, "Type not found");
        }
    }

    template<std::size_t I = 0>
    constexpr static void clear() noexcept
    {
        std::get<I>(data).clear();

        if constexpr(I + 1 != std::tuple_size_v<tuple_type>)
        {
            clear<I + 1>();
        }
    }
};

#endif
