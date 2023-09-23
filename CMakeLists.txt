cmake_minimum_required(VERSION 3.12)

project(picocanvas CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(picocanvas INTERFACE)

target_sources(picocanvas INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/canvas.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/geometry.cpp
)

target_include_directories(picocanvas INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/include
)
