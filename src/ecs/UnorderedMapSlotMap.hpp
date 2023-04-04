#ifndef UNORDERED_MAP_SLOT_MAP
#define UNORDERED_MAP_SLOT_MAP

#include <unordered_map>
#include <stack>

template <typename VALUE_TYPE, typename KEY_TYPE = std::size_t>
class UnorderedMapSlotMap {
public:
    using value_type = VALUE_TYPE;
    using key_type = KEY_TYPE;

    [[nodiscard]] constexpr auto size() const noexcept {
        return m_data.size();
    }

    [[nodiscard]] constexpr value_type & get(const key_type & key) noexcept {
        return m_data[key];
    }

    [[nodiscard]] constexpr value_type get(const key_type & key) const noexcept {
        return m_data[key];
    }

    [[nodiscard]] constexpr key_type insert(value_type && element) noexcept {
        auto id = nextId();
        m_data[id] = element;
        return id;
    }

    [[nodiscard]] constexpr key_type insert(const value_type & element) noexcept {
        auto id = nextId();
        m_data[id] = element;
        return id;
    }

    constexpr void erase(const key_type & key) noexcept {
        m_data.erase(key);
        key_stack.push(key);
    }

    [[nodiscard]] constexpr auto begin() noexcept {
        return m_data.begin();
    }

    [[nodiscard]] constexpr auto end() noexcept {
        return m_data.end();
    }

    [[nodiscard]] constexpr auto cbegin() const noexcept {
        return m_data.cbegin();
    }

    [[nodiscard]] constexpr auto cend() const noexcept {
        return m_data.cend();
    }

    constexpr void clear() noexcept {
        m_data.clear();
        current_key = 0;
        key_stack = {};
    }

private:
    [[nodiscard]] constexpr key_type nextId() noexcept {
        if (key_stack.empty()) {
            return current_key++;
        }
        else {
            auto top = key_stack.top();
            key_stack.pop();
            return top;
        }
    } 

    inline static std::unordered_map<key_type, value_type> m_data = {};
    inline static key_type current_key = 0;
    inline static std::stack<key_type> key_stack = {};
};

#endif
