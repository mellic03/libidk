cmake_minimum_required(VERSION 3.9)
project(libidk-idk_memory)


file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    PREFIX ""
    POSITION_INDEPENDENT_CODE ON
)

if (IDK_DEBUG)
    target_compile_options(${PROJECT_NAME} PUBLIC -O0 -g)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif ()



target_link_libraries(
    ${PROJECT_NAME} PUBLIC
)


file(
    GLOB PUBLIC_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)


install(
    FILES ${PUBLIC_HEADER}
    DESTINATION ${CMAKE_SOURCE_DIR}/build/include/libidk/memory/
)