cmake_minimum_required(VERSION 3.9)

if (DEFINED LIBIDK_BUILD_OBJECT)

    project(libidk)
    add_subdirectory(src/libidk/IDKgl)
    add_subdirectory(src/libidk/IDKcommon)
    add_library(${PROJECT_NAME} OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp)

    target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        IDKgl
        IDKcommon
    )
    
else()

    add_compile_options("-fPIC")

    project(idk)
    add_subdirectory(src/libidk/IDKgl)
    add_subdirectory(src/libidk/IDKcommon)
    add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp)

    target_link_libraries(
        ${PROJECT_NAME} PUBLIC
        IDKgl
        IDKcommon
    )
    
endif()
