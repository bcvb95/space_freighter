
cmake_minimum_required (VERSION 3.5.1)
project (space_freighter)


SET(CMAKE_CXX_FLAGS "-std=c++11")
add_definitions("-ggdb3")

set(CMAKE_MODULE_PATH "/usr/local/lib/x86_64-linux-gnu/cmake/" "/usr/lib/x86_64-linux-gnu/cmake/")



include_directories(include/graphics 
                    include/simulation 
                    include/core_engine 
                    include/gamemanager 
                    lib/SOIL/inc
                    lib/freetype-2.9/include
                    ) 

add_subdirectory(src)
add_subdirectory(lib/SOIL)
add_subdirectory(lib/freetype-2.9)

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_executable(space_freighter src/main.cpp)
target_link_libraries(space_freighter core_lib graphic_lib soil freetype)

add_executable(simulation_test src/simulation/main.cpp)
target_link_libraries(simulation_test simulation_lib)

#add_executable(graphical_simulation src/gamemanager/graphicalsim_main.cpp)
#target_link_libraries(graphical_simulation core_lib graphic_lib soil simulation_lib gamemanager_lib)
