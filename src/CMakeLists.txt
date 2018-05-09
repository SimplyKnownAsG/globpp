
file(GLOB GLOBPP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(globpp
        STATIC
        ${GLOBPP_SRC})

target_compile_features(globpp PUBLIC cxx_rvalue_references)

target_include_directories(globpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

