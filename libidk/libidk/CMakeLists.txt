cmake_minimum_required(VERSION 3.9)

project(IDKcommon)

file(GLOB SOURCES
    "./*.cpp"
    "idk_datastructures/*.cpp"
)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

find_package(SDL2_mixer REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_mixer_INCLUDE_DIRS})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    SDL2_mixer
)
