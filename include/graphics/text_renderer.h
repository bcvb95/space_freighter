#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <shader.h>

#include <iostream>
#include <map>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

enum FONTSIZE
{
    FS_12,
    FS_18,
    FS_24,
    FS_48,
    MAX_NUM_FONTSIZES
};

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos Advance;    // Offset to advance to next glyph
};


class TextRenderer
{
public:
    TextRenderer(TextShader* shader, std::string filename);
    
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color=glm::vec4(0,0,0,1), FONTSIZE fs_enum = FS_12);
    void LoadFont();

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


    // array of charcters-structs for each loaded fontsize
    std::map<GLchar, Character> m_characters[MAX_NUM_FONTSIZES];

    // pointer to shader
    TextShader* m_shader;

    std::string m_filename;
};


#endif