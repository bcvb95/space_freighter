#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <shader.h>

#include <iostream>
#include <map>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H


struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos Advance;    // Offset to advance to next glyph
};


class TextRenderer
{
public:
    TextRenderer(TextShader* shader);
    
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color=glm::vec4(0,0,0,1));
    void LoadFont(std::string filename, GLuint fontsize);

protected:
private:
    enum 
    {
        POSITION_VB,
        NUM_BUFFERS
    };

    // vertex attribute array
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffer;

    // storage for fontcharacters
    std::map<GLchar, Character> m_characters;

    // pointer to shader
    TextShader* m_shader;
};


#endif