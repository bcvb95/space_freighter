#include <iostream>
#include <fstream>
#include <shader.h>
#include <transform.h>
#include <glm/gtc/type_ptr.hpp>

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
    glBindAttribLocation(m_program, 2, "normal" );

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, GL_TRUE, "Error: Shaderprogram failed linking");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, GL_TRUE, "Error: Shaderprogram is invalid");

    // this->Bind();

    // projection view and model 
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "modelMat");  // model matrix
    m_uniforms[PROJMAT_U] = glGetUniformLocation(m_program, "projMat"); // model view projection matrix
    
    // Lighting properties
    m_uniforms[CAMPOS_U] = glGetUniformLocation(m_program, "camPos");
    m_uniforms[LIGHTPOS_U] = glGetUniformLocation(m_program, "lightPos");
    m_uniforms[LIGHTCOL_U] = glGetUniformLocation(m_program, "lightColor");
    
    // material properties
    m_uniforms[MATEMIS_U] = glGetUniformLocation(m_program, "matEmmissive");
    m_uniforms[MATDIFFUSE_U] = glGetUniformLocation(m_program, "matDiffuse");
    m_uniforms[MATSPEC_U] = glGetUniformLocation(m_program, "matSpecular");
    m_uniforms[MATSHINE_U] = glGetUniformLocation(m_program, "matShiny");

    // global ambient effect
    m_uniforms[MATAMBI_U] = glGetUniformLocation(m_program, "ambient");

    // check for errors finding uniform locations.
    for (unsigned int i = 0; i < NUM_UNIFORMS; i++)
    {
        if (m_uniforms[i] == -1)
        {
            std::cout << "glUniformLocation " << i << " failed" << std::endl; 
        }     
    }

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


void Shader::Update(const Transform* transform, Camera* cam)
{  
    glm::vec4 black(0);
    glm::vec4 white(1);
    glm::vec4 ambient(0.7,0.7,0.7,1.0);
    glm::vec4 grey(1); 
    grey /= 3;

    // uniforms for transforming vertex positions 
    glm::mat4 model_mat = transform->GetTransformMatrix();
    glm::mat4 proj_mat = cam->GetViewProjectionMatrix() * model_mat;
    glUniformMatrix4fv(m_uniforms[MODEL_U],1, GL_FALSE, glm::value_ptr(model_mat));
    glUniformMatrix4fv(m_uniforms[PROJMAT_U], 1,GL_FALSE, glm::value_ptr(proj_mat));

    // uniforms for lighting
    glm::vec4 cam_pos = glm::vec4(*cam->GetPos(), 1); // get camera position
    glm::vec4 light_pos = glm::vec4(0.0f,100.0f, 0.0f,1.0f);         // set lighting position // NEEDS TO BE CHANGED //
    glm::vec4 light_col = glm::vec4(1.0f,1.0f,1.0f,1.0f); // color of light (RED)

    glUniform4fv(m_uniforms[CAMPOS_U], 4, glm::value_ptr(cam_pos));
    glUniform4fv(m_uniforms[LIGHTPOS_U], 4, glm::value_ptr(light_pos));
    glUniform4fv(m_uniforms[LIGHTCOL_U], 4, glm::value_ptr(light_col));

    //uniform for material properties
    glUniform4fv(m_uniforms[MATEMIS_U], 4, glm::value_ptr(black)); 
    glUniform4fv(m_uniforms[MATDIFFUSE_U], 4, glm::value_ptr(white));
    glUniform4fv(m_uniforms[MATSPEC_U], 4 , glm::value_ptr(white));
    glUniform1f(m_uniforms[MATSHINE_U], 1000.0f);

    //global ambiance
    glUniform4fv(m_uniforms[MATAMBI_U],1, glm::value_ptr(ambient));
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
