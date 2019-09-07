cmake_minimum_required(VERSION 3.14)
project(heightmap)
set(CMAKE_CXX_STANDARD 17)
add_executable(heightmap main.cpp Surface.h Renderer.h)
target_link_libraries(heightmap
        sfml-system
        sfml-window
        sfml-graphics)