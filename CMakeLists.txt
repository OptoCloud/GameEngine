cmake_minimum_required(VERSION 3.5)

set(project GameEngine)
project(${project})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR}/GL)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC -g")

if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release")
    message("Building with no optimization (Debug build)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --verbose")
else()
    message("Building with full optimization (Release build)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

add_executable(${project}
    main.cpp
    gameloop.cpp
    gameloop.h
    )

add_subdirectory(types)
add_subdirectory(logic)
target_link_libraries(${project}
    types
    logic
    pthread
    ${OPENGL_LIBRARY}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARIES}
    )
