#pragma once

#include "Object.h"

class MySphere: public Object
{
public:
	MySphere(Shader* shader, int id);
	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 clr);
	~MySphere();
};

