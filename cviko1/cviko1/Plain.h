#pragma once

#include "Object.h"
#include "Texture.h"

class Plain : public Object
{
public:
	Plain(Shader* shader, int id);
	void setPosition(glm::vec3 position);
	void setColor(glm::vec3 clr);
	~Plain();
};

