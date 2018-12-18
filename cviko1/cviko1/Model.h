#pragma once

#include "Object.h"

class Model: public Object
{
public:
	Model(Shader* shader, int id);
	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 clr);
	~Model();
};

