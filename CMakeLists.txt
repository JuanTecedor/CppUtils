cmake_minimum_required(VERSION 3.22)

project(CppUtils VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/Math.hpp tests/testMath.cpp
    src/Vector.hpp tests/testVector.cpp
    src/OstreamRedirector.hpp tests/testOstreamRedirector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        -Werror
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
        -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation
        -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference
        -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough
)

include(CTest)
include(Catch)

catch_discover_tests(${PROJECT_NAME})
