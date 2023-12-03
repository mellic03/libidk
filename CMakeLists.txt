cmake_minimum_required(VERSION 3.9)

project(ree)

file(GLOB SOURCES
    ./dummy.cpp
)

add_subdirectory(libidk/libidk)
add_subdirectory(libidk/IDKgl)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    libidk
    IDKgl
)
