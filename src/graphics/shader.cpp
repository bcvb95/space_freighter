#include <iostream>
#include <fstream>
#include <shader.h>
#include <transform.h>


void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& filename);
GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader() {}

Shader::Shader(const std::string& filename)
{
    m_program = glCreateProgram();

    m_shaders[0] = CreateShader(LoadShader(filename+".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(filename+".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord"); 

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, GL_TRUE, "Error: Shaderprogram failed linking");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, GL_TRUE, "Error: Shaderprogram is invalid");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

}

Shader::~Shader()
{   
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}


void Shader::Bind()
{
    glUseProgram(m_program);
}


void Shader::Update(const Transform* transform, const Camera* cam)
{
    glm::mat4 t_matrix = cam->GetViewProjectionMatrix() * transform->GetTransformMatrix();
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1, GL_FALSE, &t_matrix[0][0]);
}


GLuint Shader::CreateShader(const std::string& text, GLenum type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        std::cerr << "Error: creating shader failed" << std::endl; 
    
    const GLchar* shaderSources[1];
    GLint shaderSourceLengths[1];

    shaderSources[0] = text.c_str();
    shaderSourceLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSources, shaderSourceLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compile failure");

    return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }
    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
