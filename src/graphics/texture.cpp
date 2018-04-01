#include <texture.h>
#include <SOIL.h>
#include <iostream>

Texture::Texture() {};

Texture::Texture(const char* fileName)
{

    glGenTextures(1, &m_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    int width, height;
    unsigned char* data = SOIL_load_image(fileName,&width, &height, 0, SOIL_LOAD_RGBA);

    if (data==NULL)
      std::cerr << "Unable to load texture: " << fileName << std::endl; 

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    std::cout << "Image width: " << width << std::endl; 
    std::cout << "Image height: " << height << std::endl; 

    SOIL_free_image_data(data);


}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
