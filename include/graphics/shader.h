#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <mesh.h>
#include <transform.h>
#include <camera.h>

class Shader 
{
    public:
        Shader(void);
        Shader(const std::string& filename);
        Shader(const Shader& other){}; 

        void Bind();
        virtual ~Shader();

        void Update(const Transform* transform, const Camera* cam);

    protected:
    private:
        static const unsigned int NUM_SHADERS = 2;

        std::string LoadShader(const std::string& fileName);
	    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
        GLuint CreateShader(const std::string& text, GLenum type);

        enum 
        {
            TRANSFORM_U,

            NUM_UNIFORMS
        };

        GLuint m_program;
	    GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif