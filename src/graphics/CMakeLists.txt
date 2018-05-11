

# find third party libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)


include_directories(
    ${SDL2_INCLUDE_DIRS}
	${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_DIRS}
)

add_library(graphic_lib 
            display.cpp
            text_renderer.cpp
            camera.cpp
            mesh.cpp
            shader.cpp
            texture.cpp
)   


target_link_libraries(graphic_lib
    ${GLFW3_LIBRARIES}
    ${SDL2_LIBRARIES}
   	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
    ${GLEW_LIBRARY}
)