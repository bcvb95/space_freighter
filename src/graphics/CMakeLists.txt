

# find third party libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLM REQUIRED)


include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_PATH}
    ${SDL2_IMAGE_INCLUDE_PATH}
	${GLEW_INCLUDE_PATH}
	${GLFW3_INCLUDE_PATH}
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
    ${SDL2_TTF_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${GLM_LIBRARIES}
   	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
    ${GLEW_LIBRARY}
)