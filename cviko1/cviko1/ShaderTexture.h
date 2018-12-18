#pragma once

#include <GL/glew.h>
#include <string>

#include "Shader.h"

class ShaderTexture : public Shader
{
public:
	ShaderTexture();
	//ShaderTexture(Camera *cam);
	bool ControlOfCompilation(void);
	void sendUniform(const GLchar *name, glm::mat4 data);
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void sendInt(const std::string &name, GLuint *value);
	void clearAndUse(void);
	void update();
	void update(glm::mat4 m);
	~ShaderTexture();
};

