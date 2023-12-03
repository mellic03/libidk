cmake_minimum_required(VERSION 3.9)

project(idk)

add_subdirectory(libidk/libidk)
add_subdirectory(libidk/IDKgl)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    IDKcommon
    IDKgl
)
