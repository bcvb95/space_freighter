#include_directories(${CMAKE_SOURCE_DIR}/include/simulation)

add_library( simulation_lib
             mainsim.cpp
             simutils.cpp
             generator.cpp
             universe.cpp
             world.cpp
)

#link_libraries(simulation_lib core_lib graphic_lib)
