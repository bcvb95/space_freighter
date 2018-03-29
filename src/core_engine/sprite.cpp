

#include <iostream>
#include <glm/glm.hpp>
#include <sprite.h>

Sprite::Sprite() {};

Sprite::Sprite(const std::string& tex_file, const std::string& shader_file)
{
    Vertex square_vertices[] = { Vertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), 
                      Vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),  
                      Vertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
                      Vertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f))};


    m_mesh = new Mesh(square_vertices,(sizeof(square_vertices)/sizeof(square_vertices[0])));
    m_texture = new Texture(tex_file);  
    m_shader = new Shader(shader_file);
}

Sprite::~Sprite() 
{
    delete m_mesh;
    delete m_texture;
    delete m_shader;
}

void Sprite::Draw(const Transform* transform,const Camera* cam)
{
    m_shader->Bind();
    m_texture->Bind();
    m_shader->Update(transform, cam);
    m_mesh->Draw();
}
