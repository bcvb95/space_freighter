#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
    Texture(void);
	Texture(const char* fileName);
	Texture(const Texture& texture) {};

	void Bind();

	virtual ~Texture();
protected:
private:

	GLuint m_texture;
};

#endif