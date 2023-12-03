cmake_minimum_required(VERSION 3.9)

project(IDKcommon)

file(GLOB SOURCES
    "./*.cpp"
    "idk_datastructures/*.cpp"
)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
)
