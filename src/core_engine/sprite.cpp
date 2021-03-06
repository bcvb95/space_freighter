

#include <iostream>
#include <glm/glm.hpp>
#include <sprite.h>

Sprite::Sprite(Texture* _texure, BasicShader* _shader)//const char* tex_file, const std::string& shader_file)
{ 
    glm::vec3 v1_pos(-1.0f, -1.0f, 0.0f);
    glm::vec3 v2_pos(-1.0f, 1.0f, 0.0f);
    glm::vec3 v3_pos(1.0f, -1.0f, 0.0f);
    glm::vec3 v4_pos(1.0f, 1.0f, 0.0f);

    
    Vertex square_vertices[] = { Vertex(v1_pos, glm::vec2(1.0f, 1.0f)), 
                      Vertex(v2_pos, glm::vec2(1.0f, 0.0f)),  
                      Vertex(v3_pos, glm::vec2(0.0f, 1.0f)),
                      Vertex(v4_pos, glm::vec2(0.0f, 0.0f))};
    

    m_mesh = new Mesh(square_vertices,(sizeof(square_vertices)/sizeof(square_vertices[0])));
    m_texture = _texure;  
    m_shader = _shader;
}

Sprite::~Sprite() 
{
    delete m_mesh;
}

void Sprite::Draw(const Transform* transform)
{   
    m_shader->Bind();
    m_texture->Bind();
    m_shader->Update(transform);
    m_mesh->Draw();
}