cmake_minimum_required(VERSION 3.22)

project(CppUtils VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/PreventInSourceBuilds.cmake)

find_package(Catch2 3 REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/Math.hpp
    test/testMath.cpp
    src/Vector.hpp
    test/testVector.cpp
    src/VectorTuple.hpp
    src/VectorTupleHelpers.hpp
    test/testVectorTuple.cpp
    src/OstreamRedirector.hpp
    test/testOstreamRedirector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    # -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wuseless-cast
    -O2  # Only for benchmarking
)

include(CTest)
include(Catch)

catch_discover_tests(${PROJECT_NAME})
