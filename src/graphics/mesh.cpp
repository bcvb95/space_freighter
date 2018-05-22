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

    
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> index;


    for (unsigned int i = 0; i < m_drawcount; i++)
    {
        positions.push_back(vertices[i].GetPos());
        texCoords.push_back(vertices[i].GetTexCoord());
        normals.push_back(glm::vec3(0,0,0));
    }

    glm::vec3 v1 = positions[1] - positions[0];
    glm::vec3 v2 = positions[2] - positions[0];
    glm::vec3 norm1 = glm::normalize(glm::cross(v1,v2));
    
    glm::vec3 v3 = positions[0] - positions[1];
    glm::vec3 v4 = positions[3] - positions[1];
    glm::vec3 norm2 = glm::normalize(glm::cross(v3,v4));

    glm::vec3 v5 = positions[0] - positions[2];
    glm::vec3 v6 = positions[3] - positions[2];
    glm::vec3 norm3 = glm::normalize(glm::cross(v5,v6));
    
    glm::vec3 v7 = positions[2] - positions[3];
    glm::vec3 v8 = positions[1] - positions[3];
    glm::vec3 norm4 = glm::normalize(glm::cross(v7, v8));

    normals[0] += norm1;
    normals[1] += norm2;
    normals[2] += norm3;
    normals[3] += norm4;

    for(unsigned int i = 0; i < positions.size(); i++)
        normals[i] = glm::normalize(normals[i]);

    positions.reserve(numVertices);
    texCoords.reserve(numVertices);
    normals.reserve(numVertices);

    glGenBuffers(NUM_BUFFERS, &m_vertexArrayBuffers[0]);

    // set GL buffers for vertex positions.
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);

    // set GL buffers for texture coordinates.
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEXCOORD_VB);
    glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
   // set Gl buffers for vertex normals
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMALS_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMALS_VB);
    glVertexAttribPointer(NORMALS_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() 
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}