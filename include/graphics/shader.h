#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <mesh.h>
#include <transform.h>
#include <camera.h>

// Shader helper function declarations
std::string LoadShader(const std::string& fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
GLuint CreateShader(const std::string& text, GLenum type);


class Shader 
{
    public:
        Shader(const std::string& filename, Camera* cam);
        void Bind();

        Camera* GetCam() {return m_cam;}

        virtual ~Shader();
    protected:
        static const unsigned int NUM_SHADERS = 2;
        GLuint m_program;
	    GLuint m_shaders[NUM_SHADERS];

        Camera* m_cam;
    private:
};

class GUI_Shader : public Shader
{
public:
    GUI_Shader(const std::string filename, Camera* cam);
    void Update(Camera* cam);
private:
    enum
    {
        PROJMAT_U,
        NUM_UNIFORMS
    };

    GLuint m_uniforms[NUM_UNIFORMS];

    glm::mat4 m_uiRect;
};

class TextShader : public Shader
{
public:
    TextShader(const std::string filename, Camera* cam);
    void Update(Camera* cam, glm::vec4 col);
private:
    enum // basic shader enum 
    {
        // vertex shader uniform handles
        PROJMAT_U,
        COLOR_U,
        NUM_UNIFORMS
    };

    GLuint m_uniforms[NUM_UNIFORMS];

    glm::mat4 m_uiRect;
};

class BasicShader : public Shader
{   
public:
    BasicShader(const std::string& filename, Camera* cam);
    void Update(const Transform* transform);
protected:
private:
        enum // basic shader enum 
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

            MATAMBI_U,   // global ambiance
            NUM_UNIFORMS 
        };
        GLuint m_uniforms[NUM_UNIFORMS];
};


#endif