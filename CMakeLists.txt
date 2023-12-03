cmake_minimum_required(VERSION 3.9)

project(idk)

# file(GLOB SOURCES
#     ./dummy.cpp
# )

add_subdirectory(libidk/libidk)
add_subdirectory(libidk/IDKgl)
add_library(${PROJECT_NAME} STATIC ${SOURCES})


# add_executable(${PROJECT_NAME} "./dummy.cpp")

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    # ${CMAKE_SOURCE_DIR}/output/lib/libidk/libidk.a
    libidk
    IDKgl
)
