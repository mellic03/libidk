cmake_minimum_required(VERSION 3.9)
project(libidk)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libidk/GL/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/libidk/memory/)


file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libidk/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libidk/containers/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    PREFIX ""
    POSITION_INDEPENDENT_CODE ON
)

if (IDK_DEBUG)
    target_compile_options(${PROJECT_NAME} PUBLIC -Werror -fsanitize=undefined -lstdc++fs -g)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif ()



target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    IDKGL
    libidk-idk_memory
    GLEW
    SDL2
    SDL2_image
)


FILE(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/libidk
    DESTINATION ${IDK_OUTPUT_DIRECTORY}/include/.
)


# file(
#     GLOB PUBLIC_HEADER
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/libidk/*.hpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/libidk/*.inl
# )

# install(
#     FILES ${PUBLIC_HEADER}
#     DESTINATION ${IDK_OUTPUT_DIRECTORY}/
# )