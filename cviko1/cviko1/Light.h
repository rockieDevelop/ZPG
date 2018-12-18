#pragma once

#include "Object.h"

class Light: public Object
{
private:
	int lightId;
	Shader* shader;
public:
	Light(Shader* shader, int id, int lightId);
	~Light();

	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 clr);
};

