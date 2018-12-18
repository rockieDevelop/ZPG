#include "Model.h"



Model::Model(Shader* shader, int id) : Object(shader, id)
{
	model = true;
}

void Model::setPosition(glm::vec3 position) {
	M = glm::scale(glm::translate(glm::mat4(1.f), position), scaleVec);
	notify();
}

void Model::setColor(glm::vec3 clr) {
	color = clr;
}

Model::~Model()
{
}
