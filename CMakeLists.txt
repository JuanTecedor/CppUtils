cmake_minimum_required(VERSION 3.22)

project(CppUtils VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/Vector.hpp src/Math.hpp src/ecs/SlotMapInterface.hpp src/ecs/UnorderedMapSlotMap.hpp src/ecs/SlotMap.hpp
    tests/testVector.cpp tests/testMath.cpp tests/ecs/testUnorderedMapSlotMap.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(${PROJECT_NAME})