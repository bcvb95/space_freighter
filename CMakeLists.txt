
cmake_minimum_required (VERSION 3.5.1)
project (space_freighter)

add_definitions("-std=c++11")

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_MODULE_PATH "/usr/local/lib/x86_64-linux-gnu/cmake/" "/usr/lib/x86_64-linux-gnu/cmake/")

include_directories(include/graphics include/core_engine include/simulation)

add_subdirectory(src)

add_executable(space_freighter src/main.cpp)
target_link_libraries(space_freighter core_lib graphic_lib)

add_executable(simulation_test src/simulation/main.cpp)
target_link_libraries(simulation_test simulation_lib)
