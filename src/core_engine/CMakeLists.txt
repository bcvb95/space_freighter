
#include_directories(${CMAKE_SOURCE_DIR}/include/core_engine)

add_library(core_lib 
            gameobject.cpp
            sprite.cpp
            input_handler.cpp
            gui_objects.cpp
            core_utils.cpp
)   
