#include "Light.h"
#include "sphere.h"


Light::Light(Shader* sh, int id, int lightId) : Object(sh, id)
{	
		this->lightId = lightId;
		shader = sh;
		//vertex buffer object (VBO)
		VBO = 0;
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//if(type == 0)
		glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);
		//else
			//glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);
		//vertex attribute object(VAO)
		VAO = 0;
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

		scaleVec = glm::vec3(0.2, 0.2, 0.2);
		ambientStrength = 1.0;
}

void Light::setPosition(glm::vec3 position) {
	M = glm::scale(glm::translate(glm::mat4(1.f), position), scaleVec);
	//shader->setVec3("lightPos", position);
	shader->setVec3("lights[" + std::to_string(lightId) + "].lightPos", position);
	notify();
}

void Light::setColor(glm::vec3 clr) {
	color = clr;
	//shader->setVec3("lightColor", color);
	shader->setVec3("lights[" + std::to_string(lightId) + "].lightColor", color);
}

Light::~Light()
{
}
