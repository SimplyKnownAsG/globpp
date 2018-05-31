cmake_minimum_required(VERSION 3.8)

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(globpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

option(GLOBPP_TESTS  "Enable testing" ON)

if(GLOBPP_TESTS)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
