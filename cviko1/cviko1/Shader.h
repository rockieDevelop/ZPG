#pragma once

#include <GL/glew.h>
#include <string>

#include "Observer.h"

class Shader : public Observer
{
protected:
	GLuint shaderID;
	GLuint vertexShader;
	GLuint fragmentShader;
public:
	Shader();
	Shader(const char* vShader, const char* fShader, Camera *cam);
	~Shader();

	//bool ControlOfCompilation(void);
	void useProgram(void);
	void sendUniform(const GLchar *name, glm::mat4 data);
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setFloat(const std::string &name, float a) const;
	void setInt(const std::string &name, int a) const;
	void setMat4(const std::string &name, glm::mat4 mat);
	void sendInt(const std::string &name);
	void sendTexture(int id);
	void Shader::sendTexture(const std::string &name, const std::string &number, unsigned int i);
	void clearAndUse(void);
	void update();
	void update(glm::mat4 m);
};

