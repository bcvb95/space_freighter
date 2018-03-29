#include <mesh.h>
#include <vector>
#include <algorithm>

Mesh::Mesh() {}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
    m_drawcount = numVertices;
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    for (unsigned int i = 0; i < m_drawcount; i++)
    {
        positions.push_back(vertices[i].GetPos());
        texCoords.push_back(vertices[i].GetTexCoord());
    }

    positions.reserve(numVertices);
    texCoords.reserve(numVertices);

    // set GL buffers for vertex positions.
    glGenBuffers(NUM_BUFFERS, &m_vertexArrayBuffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);

    // set GL buffers for texture coordinates.
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEXCOORD_VB);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindVertexArray(0);

}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void Mesh::Draw() 
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_QUADS, 0, m_drawcount);

    glBindVertexArray(0);
}