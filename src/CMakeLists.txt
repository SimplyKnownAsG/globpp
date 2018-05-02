
add_library(globpp
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/globpp.cpp)

target_compile_features(globpp PUBLIC cxx_rvalue_references)

target_include_directories(globpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

