#include <texture.h>
#include <SOIL.h>
#include <iostream>

Texture::Texture() {};

Texture::Texture(const char* fileName)
{

    glGenTextures(1, &m_texture);
        
    m_texture = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (m_texture==0)
      std::cerr << "Unable to load texture: " << fileName << std::endl; 

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glBindTexture(GL_TEXTURE_2D, m_texture);

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
