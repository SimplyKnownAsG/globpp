file(GLOB GLOBPP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB GLOBPP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(globpp
        STATIC
        ${GLOBPP_SRC})

target_compile_features(globpp PUBLIC cxx_rvalue_references)

target_include_directories(globpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(globpp
        PROPERTIES
        PUBLIC_HEADER ${GLOBPP_HEADERS})

install(TARGETS globpp 
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
