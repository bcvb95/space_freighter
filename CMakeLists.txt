
cmake_minimum_required (VERSION 3.5.1)
project (project_test )

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_MODULE_PATH "/usr/local/lib/x86_64-linux-gnu/cmake/" "/usr/lib/x86_64-linux-gnu/cmake/")

include_directories(include/graphics include/core_engine)

add_subdirectory(src)

add_executable(project_test src/main.cpp)
target_link_libraries(project_test core_lib graphic_lib)

