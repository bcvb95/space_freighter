#include <iostream>
#include <fstream>
#include <shader.h>
#include <transform.h>

//////////////////////////////////////////////////////////////////
// Base Shader Class
//////////////////////////////////////////////////////////////////////


Shader::Shader(const std::string& filename, Camera* cam)
{
    m_program = glCreateProgram();

    m_shaders[0] = CreateShader(LoadShader(filename+".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(filename+".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, GL_TRUE, "Error: Shaderprogram failed linking");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, GL_TRUE, "Error: Shaderprogram is invalid");

    m_cam = cam;

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

//////////////////////////////////////////////////////////////////
// GUI shader 
//////////////////////////////////////////////////////////////////

GUI_Shader::GUI_Shader(const std::string filename, Camera* cam) : Shader(filename, cam)
{
    this->Bind();
    glBindAttribLocation(this->m_program, 0, "position");
    m_uniforms[PROJMAT_U] = glGetUniformLocation(this->m_program, "projMat");
    m_uniforms[BORDERWIDTH_U] = glGetUniformLocation(this->m_program, "border_width");
    m_uniforms[BORDERCOLOR_U] = glGetUniformLocation(this->m_program, "border_color");
    m_uniforms[ASPECT_U] = glGetUniformLocation(this->m_program, "aspect");


    glUniform1i(glGetUniformLocation(this->m_program, "tex"), 0);


    // check for errors finding uniform locations.
    for (unsigned int i = 0; i < NUM_UNIFORMS; i++)
    {
        if (m_uniforms[i] == -1)
        {
            std::cout << "glUniformLocation " << i << " failed" << std::endl; 
        }     
    }

    m_cam = cam;

    // set default rect for creating orthographic camera (the size of the window)
    m_uiRect =  glm::ortho(0.0f, (float)cam->GetWindow()->GetWindowWidth(), (float)cam->GetWindow()->GetWindowHeight(), 0.0f, -1.0f, 1000.0f);
    glUniformMatrix4fv(m_uniforms[PROJMAT_U],1, GL_FALSE, glm::value_ptr(m_uiRect));
}

void GUI_Shader::SetBorderProps(float border_width, glm::vec4 border_col, glm::vec2 size) {
    this->Bind();
    // uniforms for transforming vertex positions 
    glUniform1f(m_uniforms[BORDERWIDTH_U], border_width);
    glUniform4fv(m_uniforms[BORDERCOLOR_U], 1, glm::value_ptr(border_col));

    float aspect;
    if (size.x > size.y) {
        aspect = size.x / size.y; 
    } else {
        aspect = size.y / size.x; 
    }
    glUniform1fv(m_uniforms[ASPECT_U], 1, &aspect);
}

void GUI_Shader::SetProjectionMat (glm::vec4 ortho_rect) {
    this->Bind();
    glm::mat4 proj_mat = glm::ortho((float)ortho_rect.x, (float)ortho_rect.y, (float)ortho_rect.z, (float)ortho_rect.w, -1.0f, 1000.0f);
    glUniformMatrix4fv(m_uniforms[PROJMAT_U],1, GL_FALSE, glm::value_ptr(proj_mat));
}

//////////////////////////////////////////////////////////////////
// GUI_Bound Shader 
//////////////////////////////////////////////////////////////////

GUI_RectBoundShader::GUI_RectBoundShader(const std::string filename, Camera* cam) : Shader(filename, cam)
{
    this->Bind();

    glBindAttribLocation(this->m_program, 0, "position");
    m_uniforms[PROJMAT_U] = glGetUniformLocation(this->m_program, "projMat");
    m_uniforms[BORDERWIDTH_U] = glGetUniformLocation(this->m_program, "border_width");
    m_uniforms[BORDERCOLOR_U] = glGetUniformLocation(this->m_program, "border_color");
    m_uniforms[ASPECT_U] = glGetUniformLocation(this->m_program, "aspect");
    m_uniforms[BOUNDRECT_U] = glGetUniformLocation(this->m_program, "boundRect");

    glUniform1i(glGetUniformLocation(this->m_program, "tex"), 0);

    // check for errors finding uniform locations.
    for (unsigned int i = 0; i < NUM_UNIFORMS; i++)
    {
        if (m_uniforms[i] == -1)
        {
            std::cout << "glUniformLocation " << i << " failed" << std::endl; 
        }     
    }

    m_cam = cam;

    m_uiRect =  glm::ortho(0.0f, (float)cam->GetWindow()->GetWindowWidth(), (float)cam->GetWindow()->GetWindowHeight(), 0.0f, -1.0f, 1000.0f);
    glUniformMatrix4fv(m_uniforms[PROJMAT_U],1, GL_FALSE, glm::value_ptr(m_uiRect));
}


void GUI_RectBoundShader::SetBorderProps(float border_width, glm::vec4 border_col, glm::vec2 size) {
    this->Bind();
    // uniforms for transforming vertex positions 
    glUniform1f(m_uniforms[BORDERWIDTH_U], border_width);
    glUniform4fv(m_uniforms[BORDERCOLOR_U], 1, glm::value_ptr(border_col));

    float aspect;
    if (size.x > size.y) {
        aspect = size.x / size.y; 
    } else {
        aspect = size.y / size.x; 
    }
    glUniform1fv(m_uniforms[ASPECT_U], 1, &aspect);
}

void GUI_RectBoundShader::SetProjectionMat (glm::vec4 ortho_rect) {
    this->Bind();
    glm::mat4 proj_mat = glm::ortho((float)ortho_rect.x, (float)ortho_rect.y, (float)ortho_rect.z, (float)ortho_rect.w, -1.0f, 1000.0f);
    glUniformMatrix4fv(m_uniforms[PROJMAT_U],1, GL_FALSE, glm::value_ptr(proj_mat));
}

//////////////////////////////////////////////////////////////////
// Text shader 
//////////////////////////////////////////////////////////////////

TextShader::TextShader(const std::string filename, Camera* cam) : Shader(filename, cam)
{
    this->Bind();
    glBindAttribLocation(this->m_program, 0, "position");

    glUniform1i(glGetUniformLocation(this->m_program, "tex"), 0);

    m_uniforms[PROJMAT_U] = glGetUniformLocation(this->m_program, "projMat");
    m_uniforms[COLOR_U] = glGetUniformLocation(this->m_program, "color");

    // check for errors finding uniform locations.
    for (unsigned int i = 0; i < NUM_UNIFORMS; i++)
    {
        if (m_uniforms[i] == -1)
        {
            std::cout << "glUniformLocation " << i << " failed" << std::endl; 
        }     
    }

    m_uiRect =  glm::ortho(0.0f, (float)cam->GetWindow()->GetWindowWidth(), (float)cam->GetWindow()->GetWindowHeight(), 0.0f, -1.0f, 1000.0f);
}

void TextShader::Update (Camera* cam, glm::vec4 text_color) {
    this->Bind();
    // uniforms for transforming vertex positions 
    glUniformMatrix4fv(m_uniforms[PROJMAT_U], 1,GL_FALSE, glm::value_ptr(m_uiRect));

    glUniform4fv(m_uniforms[COLOR_U], 1, glm::value_ptr(text_color));
}

//////////////////////////////////////////////////////////////////
// Basic Shader 
//////////////////////////////////////////////////////////////////

BasicShader::BasicShader(const std::string& filename, Camera* cam) : Shader(filename, cam)
{
    this->Bind();
    // projection view and model 
    glBindAttribLocation(this->m_program, 0, "position");
    glBindAttribLocation(this->m_program, 1, "texCoord"); 
    glBindAttribLocation(this->m_program, 2, "normal" );
    
    glUniform1i(glGetUniformLocation(this->m_program, "diffuseSampler"), 0);
    
    m_uniforms[MODEL_U] = glGetUniformLocation(this->m_program, "modelMat");  // model matrix
    m_uniforms[PROJMAT_U] = glGetUniformLocation(this->m_program, "projMat"); // model view projection matrix
    
    // Lighting properties
    m_uniforms[CAMPOS_U] = glGetUniformLocation(this->m_program, "camPos");
    m_uniforms[LIGHTPOS_U] = glGetUniformLocation(this->m_program, "lightPos");
    m_uniforms[LIGHTCOL_U] = glGetUniformLocation(this->m_program, "lightColor");
    
    // material properties
    m_uniforms[MATEMIS_U] = glGetUniformLocation(this->m_program, "matEmmissive");
    m_uniforms[MATDIFFUSE_U] = glGetUniformLocation(this->m_program, "matDiffuse");
    m_uniforms[MATSPEC_U] = glGetUniformLocation(this->m_program, "matSpecular");
    m_uniforms[MATSHINE_U] = glGetUniformLocation(this->m_program, "matShiny");

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

void BasicShader::Update(const Transform* transform)
{  
    this->Bind();
    glm::vec4 black(0);
    glm::vec4 white(1);
    glm::vec4 ambient(0.7,0.7,0.7,1.0);
    glm::vec4 grey(1); 
    grey /= 3;

    // uniforms for transforming vertex positions 
    glm::mat4 model_mat = transform->GetTransformMatrix();
    glm::mat4 proj_mat = m_cam->GetViewProjectionMatrix() * model_mat;
    glUniformMatrix4fv(m_uniforms[MODEL_U],1, GL_FALSE, glm::value_ptr(model_mat));
    glUniformMatrix4fv(m_uniforms[PROJMAT_U], 1,GL_FALSE, glm::value_ptr(proj_mat));

    // uniforms for lighting
    glm::vec4 cam_pos = glm::vec4(*m_cam->GetPos(), 1); // get camera position
    glm::vec4 light_pos = glm::vec4(0.0f,100.0f, 0.0f,1.0f); // set lighting position // NEEDS TO BE CHANGED //
    glm::vec4 light_col = glm::vec4(1.0f,1.0f,1.0f,1.0f); // color of light (RED)

    glUniform4fv(m_uniforms[CAMPOS_U], 4, glm::value_ptr(cam_pos));
    glUniform4fv(m_uniforms[LIGHTPOS_U], 4, glm::value_ptr(light_pos));
    glUniform4fv(m_uniforms[LIGHTCOL_U], 4, glm::value_ptr(light_col));

    //uniform for material properties
    glUniform4fv(m_uniforms[MATEMIS_U], 4, glm::value_ptr(black)); 
    glUniform4fv(m_uniforms[MATDIFFUSE_U], 4, glm::value_ptr(white));
    glUniform4fv(m_uniforms[MATSPEC_U], 4 , glm::value_ptr(white));
    glUniform1f(m_uniforms[MATSHINE_U], 100.0f);

    //global ambiance
    glUniform4fv(m_uniforms[MATAMBI_U],1, glm::value_ptr(ambient));
}


// Shader helper functions

GLuint CreateShader(const std::string& text, GLenum type)
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

std::string LoadShader(const std::string& fileName)
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

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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
