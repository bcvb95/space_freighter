#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <iostream>
#include <map>
#include <shader.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class TextRenderer  
{
public:
    TextRenderer(const char* font_file, TextShader* shader);
    void DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color); 

protected:
private:
    static const int NUM_TEXTURES = 128u;

    TextShader* m_shader;

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffer;
    GLuint m_texture[NUM_TEXTURES];

    std::map<GLuint, Character> m_characters;
};

const char* getErrorString(FT_Error err);

#endif