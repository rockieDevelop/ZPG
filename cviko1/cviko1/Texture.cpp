#include "Texture.h"
#include <soil.h>

#include "stb_image.h"



Texture::Texture()
{
}

void Texture::setTextureUnit(GLuint texture, int id) {
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture()
{
}
