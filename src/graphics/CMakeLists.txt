
# find third party libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(SDL2 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLM REQUIRED)

include_directories(
	${GLEW_INCLUDE_PATH}
	${GLFW3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

add_library(graphic_lib 
            display.cpp
            camera.cpp
            mesh.cpp
            shader.cpp
            texture.cpp
)   

target_link_libraries(graphic_lib
    ${SDL2_LIBRARIES}
    ${GLFW3_LIBRARIES}
    ${GLM_LIBRARIES}
   	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
    ${GLEW_LIBRARY}
)