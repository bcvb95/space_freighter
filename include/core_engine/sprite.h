#ifndef SPRITE_H
#define SPRITE_H

#include <algorithm>
#include <iostream>
#include <mesh.h>
#include <texture.h>
#include <shader.h>
#include <camera.h>


class Sprite
{
public:
    Sprite();
    Sprite(const std::string& tex_file, const std::string& shader_file);
    Sprite(const Sprite& other) {};
    virtual ~Sprite();

    Mesh* GetMesh() {return m_mesh;}
    Texture* GetTexture() {return m_texture;}
    Shader* GetShader() {return m_shader;}

    void Draw(const Transform* transform, const Camera* cam); 

    void SetTexture(Texture* tex)
    {
        m_texture = tex;
    }

protected:
private:

    Mesh* m_mesh;
    Texture* m_texture;
    Shader* m_shader; 
};
#endif