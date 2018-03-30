#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
    {
        this->pos = pos;
        this->texCoord = texCoord;
    }

    glm::vec3 GetPos() {return pos;}
    glm::vec2 GetTexCoord() {return texCoord;}
    glm::vec3 GetNormal() {return normal;}

protected:
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Mesh
{
    public:
        Mesh(void);
        Mesh(Vertex* vertices, unsigned int num_vertices);

        Mesh& operator= (const Mesh& other) 
        {
            if (this != &other)
            {
                m_vertexArrayObject = other.m_vertexArrayObject;
                m_drawcount = other.m_drawcount;
                for (unsigned int i = 0; i < other.NUM_BUFFERS; i++)
                    m_vertexArrayBuffers[i] = other.m_vertexArrayBuffers[i];
            }
            return *this;
        };

        void Draw();
        virtual ~Mesh();
    protected:
    private:

        enum 
        {
            POSITION_VB,
            TEXCOORD_VB,
            NORMALS_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        GLsizei m_drawcount;
};

#endif