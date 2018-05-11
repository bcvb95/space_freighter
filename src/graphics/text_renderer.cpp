#include <text_renderer.h>

TextRenderer::TextRenderer(TextShader* shader, std::string filename)
{
    m_shader = shader;
    m_filename = filename;
    
    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->m_vertexArrayObject);
    glGenBuffers(1, &m_vertexArrayBuffer);

    glBindVertexArray(this->m_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->LoadFont();
}

void TextRenderer::LoadFont() 
{
    // init FreeType library
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "could not initialize FreeType library\n");
    }

    // load all sizes
    for (int i = 0; i < MAX_NUM_FONTSIZES; i++) {

        // Load ttf font.
        FT_Face font_face;
        if (FT_New_Face(ft, m_filename.c_str(), 0, &font_face)) {
            fprintf(stderr,"Could not load true-type font %s\n", m_filename.c_str());
        }

        int fs;

        switch (i) {
            case 0:
                fs = 12;
                break;
            case 1:
                fs = 18;
                break;
            case 2:
                fs = 24;
                break;
            case 3:
                fs = 48;
                break;
        };

        FT_Set_Pixel_Sizes(font_face, 0, fs);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        this->m_characters[i].clear();


        for (GLubyte c = 0; c<130; c++)
        {
            // Load character glyph 
            if (FT_Error err = FT_Load_Char(font_face , c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph. ERROR: " << err << std::endl;
                continue;
            }


            // Generate texture
            GLuint texture;
            glActiveTexture(GL_TEXTURE0);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
    
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                font_face->glyph->bitmap.width,
                font_face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                font_face->glyph->bitmap.buffer
                );

            // Set texture options
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Now store character for later use
            Character character = {
                texture,
                glm::ivec2(font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows),
                glm::ivec2(font_face->glyph->bitmap_left, font_face->glyph->bitmap_top),
                font_face->glyph->advance.x
            };
            this->m_characters[i].insert(std::pair<GLchar, Character>(c, character));

        };
        glBindTexture(GL_TEXTURE_2D, 0);
        // Destroy FreeType once we're finished
        FT_Done_Face(font_face);
    };    
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color, FONTSIZE fs_enum)
{
    glm::vec2 text_size(0);
    
    // bind and update textshader
    m_shader->Bind();
    m_shader->Update(m_shader->GetCam(), color);

    glBindVertexArray(this->m_vertexArrayObject);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = this->m_characters[fs_enum][*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y + (this->m_characters[fs_enum]['H'].Bearing.y - ch.Bearing.y) * scale;  

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 },
            { xpos,     ypos,       0.0, 0.0 },

            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 }
        };
        
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
        glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}
