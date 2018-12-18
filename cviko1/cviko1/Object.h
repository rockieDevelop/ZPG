#pragma once

#include "Observer.h"
#include "Shader.h"

#include <vector>

class Object
{
protected:
	std::vector < Observer * > observers;
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	float ambientStrength = 0.2;
	int ID;
	int texture = -1;
	bool model = false;
	int indicesCount = 0;

	glm::mat4 M = glm::mat4(1.0f);
	glm::vec3 color = glm::vec3(1.0f);
	glm::vec3 scaleVec = glm::vec3(1.f, 1.f, 1.f);
public:
	Object(Shader* shader, int id);
	~Object();
	void makeObject(void);

	void rotate(float rotation, float x, float y, float z);
	void translate(glm::vec3 t);
	void scale(glm::vec3 s);
	void load(std::string fileName);

	virtual void setPosition(glm::vec3 position);
	virtual void setColor(glm::vec3 clr);
	void setTexture(int texture);
	glm::vec3 getColor(void);
	glm::mat4 getModel(void);
	float getAmbientStrength(void);
	int getTexture(void);
	int getID(void);
	bool isModel(void);

	void attach(Observer *obs);
	void notify();
};

