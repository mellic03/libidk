cmake_minimum_required(VERSION 3.9)
project(libidk)


file(GLOB SOURCES
    "src/libidk/*.cpp"
    "src/libidk/containers/*.cpp"
    "src/libidk/GL/*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    PREFIX ""
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 17
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()


target_link_libraries(
    ${PROJECT_NAME} PUBLIC
)

