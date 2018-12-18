#pragma once

#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture();
	void setTextureUnit(GLuint texture, int id);

	~Texture();
};

