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
    Sprite(Texture*, BasicShader*);
    virtual ~Sprite();

    Mesh* GetMesh() {return m_mesh;}
    Texture* GetTexture() {return m_texture;}
    BasicShader* GetShader() {return m_shader;}

    void Draw(const Transform* transform); 

    void SetTexture(Texture* tex)
    {
        m_texture = tex;
    }

protected:
private:

    Mesh* m_mesh;
    Texture* m_texture;
    BasicShader* m_shader; 
};
#endif