cmake_minimum_required(VERSION 3.9)

project(IDKgl)

file(GLOB SOURCES
    "./*.cpp"
)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_image_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    GLEW
    SDL2
    SDL2_image
    ${OPENGL_LIBRARIES}
    ${EXTRA_LIBS}
)
