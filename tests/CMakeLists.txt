file(DOWNLOAD
        https://github.com/catchorg/Catch2/releases/download/v1.12.2/catch.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/3rd-party/catch.hpp)

file(GLOB TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Make test executable
add_executable(globpp_tests ${TEST_SOURCES})

target_link_libraries(globpp_tests globpp)
target_include_directories(globpp_tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/3rd-party)

target_compile_features(globpp_tests PRIVATE cxx_range_for cxx_auto_type)

# the ctest thing is far too complicated...
add_custom_command(
        TARGET globpp_tests
        POST_BUILD
        COMMAND $<TARGET_FILE:globpp_tests>)
