cmake_minimum_required(VERSION 3.0)

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(globpp_tests)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(DOWNLOAD
     https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp
     ${CMAKE_BINARY_DIR}/catch.hpp)

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
include_directories(${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Make test executable
add_executable(run_tests ${TEST_SOURCES})
target_compile_features(run_tests PRIVATE cxx_noexcept cxx_range_for cxx_auto_type)

