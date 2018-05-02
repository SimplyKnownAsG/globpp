cmake_minimum_required(VERSION 3.8)

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(globpp_tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(DOWNLOAD
        https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp
        ${CMAKE_BINARY_DIR}/3rd/catch.hpp)

include_directories(${CMAKE_BINARY_DIR}/3rd)

file(GLOB TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Make test executable
add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests globpp)
target_compile_features(run_tests PRIVATE cxx_noexcept cxx_range_for cxx_auto_type)


# the ctest thing is far too complicated...
add_custom_command(
        TARGET run_tests
        POST_BUILD
        COMMAND $<TARGET_FILE:run_tests>)

