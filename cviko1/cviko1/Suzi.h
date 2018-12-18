#pragma once

#include "Object.h"

class Suzi: public Object
{
public:
	Suzi(Shader* shader, int id);
	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 clr);
	~Suzi();
};

