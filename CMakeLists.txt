cmake_minimum_required(VERSION 3.9)

set(CMAKE_BUILD_PARALLEL_LEVEL 8)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wuninitialized -Winit-self -Wmaybe-uninitialized -Werror -fsanitize=undefined -fdiagnostics-color=always -lstdc++fs")
add_compile_options("-g" "-fPIC" "-fno-ident" "-fno-asynchronous-unwind-tables")
add_definitions(-DIDK_DEBUG)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

project(idk)

file(GLOB SOURCES
    "src/*.cpp"
    "src/containers/*.cpp"
    "src/GL/*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
)

