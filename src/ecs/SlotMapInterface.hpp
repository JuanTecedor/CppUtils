#ifndef SLOT_MAP_INTERFACE
#define SLOT_MAP_INTERFACE

#include <cstddef>

template <typename VALUE_TYPE, typename KEY_TYPE = std::size_t>
struct SlotMapTypes {
    using value_type = VALUE_TYPE;
	using key_type = KEY_TYPE;
	using iterator = value_type *;
	using const_iterator = value_type const *;
};

template <typename VALUE_TYPE, typename KEY_TYPE = std::size_t>
class SlotMapInterface : public SlotMapTypes<VALUE_TYPE, KEY_TYPE> {
public:
    using value_type = SlotMapTypes<VALUE_TYPE, KEY_TYPE>::SlotMapTypes::value_type;
    using key_type = SlotMapTypes<VALUE_TYPE, KEY_TYPE>::SlotMapTypes::key_type;
    using iterator = SlotMapTypes<VALUE_TYPE, KEY_TYPE>::SlotMapTypes::iterator;
    using const_iterator = SlotMapTypes<VALUE_TYPE, KEY_TYPE>::SlotMapTypes::const_iterator;

    [[nodiscard]] consteval std::size_t size() const noexcept = delete;

    [[nodiscard]] consteval value_type & get(const auto & key) noexcept = delete;

    [[nodiscard]] consteval value_type get(const auto & key) const noexcept = delete;

    [[nodiscard]] consteval key_type insert(value_type && element) noexcept = delete;

    [[nodiscard]] consteval key_type insert(const value_type & element) noexcept = delete;

    consteval void erase(const key_type & key) noexcept = delete;

    [[nodiscard]] consteval iterator begin() noexcept = delete;

    [[nodiscard]] consteval iterator end() noexcept = delete;

    [[nodiscard]] consteval const_iterator cbegin() const noexcept = delete;

    [[nodiscard]] consteval const_iterator cend() const noexcept = delete;

    consteval static void clear() noexcept = delete;
};

#endif
