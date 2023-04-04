#include <catch2/catch_test_macros.hpp>

#include "../../src/ecs/UnorderedMapSlotMap.hpp"
#include "../../src/ecs/SlotMap.hpp"

TEST_CASE("Test UnorderedMapSlotMap") {
    UnorderedMapSlotMap<int> map;
    auto k1 = map.insert(10);
    auto id = 20;
    auto k2 = map.insert(id);
    auto k3 = map.insert(id);
    REQUIRE(k1 == 0);
    REQUIRE(k2 == 1);
    REQUIRE(k3 == 2);
    map.erase(k2);
    k2 = map.insert(id);
    REQUIRE(k2 == 1);

    for(const auto & e : map) {
    }
    map.clear();
}

TEST_CASE("Test SlotMap") {
    using SlotMap_t = SlotMap<UnorderedMapSlotMap<int>, UnorderedMapSlotMap<bool>>; 
    SlotMap_t slotMap;
    auto & intSlotMap = SlotMap_t::get<int>();
    auto id = intSlotMap.insert(10);
    
    REQUIRE(intSlotMap.get(id) == 10);
    REQUIRE(intSlotMap.size() == 1);
    REQUIRE(slotMap.get<bool>().size() == 0);

    intSlotMap.erase(id);
    REQUIRE(intSlotMap.size() == 0);

    slotMap.clear();
}
