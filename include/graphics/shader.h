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
        Shader(const std::string& filename);

        void Bind();
        virtual ~Shader();

        void Update(const Transform* transform, Camera* cam);

    protected:
    private:
        static const unsigned int NUM_SHADERS = 2;

        std::string LoadShader(const std::string& fileName);
	    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
        GLuint CreateShader(const std::string& text, GLenum type);

        enum 
        {
            // Vertex shader uniform handles
            MODEL_U,    // model transform matrix
            PROJMAT_U,  // model view proj matrix
    
            // Fragment shader uniform handles
            CAMPOS_U,   // camera pos in worldspace             
            LIGHTPOS_U, // lightpos in worldspace
            LIGHTCOL_U, // light color
            
            MATEMIS_U,  // material emmisive 
            MATDIFFUSE_U,// material diffuse
            MATSPEC_U,   // materal specular
            MATSHINE_U,  // material shiniess
            MATAMBI_U,
            NUM_UNIFORMS 
        };

        GLuint m_program;
	    GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif