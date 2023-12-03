cmake_minimum_required(VERSION 3.9)
# add_compile_options("-fPIC")

project(idk)

file(GLOB SOURCES
    "./dummy.cpp"
)

add_subdirectory(libidk/libidk)
add_subdirectory(libidk/IDKgl)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    IDKcommon
    IDKgl
)
