#include "Renderer.h"
#include "Shader.h"
#include "Object.h"

Renderer* Renderer::single = NULL;

Renderer* Renderer::getInstance(GLFWwindow* win)
{
	if (single == NULL)
	{
		single = new Renderer(win);
		return single;
	}
	return single;
}

Renderer::Renderer(GLFWwindow* win)
{
	window = win;
	printf("Renderer \n");
}

void Renderer::init(void) {
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
}

void Renderer::render(Shader* shader, std::vector<Object> objects) {
	
	for (std::vector<Object>::size_type i = 0; i != objects.size(); i++) {
		shader->sendUniform("modelMatrix", objects[i].getModel());
		shader->setVec3("objectColor", objects[i].getColor());
		shader->setFloat("ambientStrength", objects[i].getAmbientStrength());
		if (objects[i].getTexture() >= 0) {
			shader->sendTexture(objects[i].getTexture());
		}
		objects[i].makeObject();
	}
}

void Renderer::render(Shader* shader, Object obj) {
	shader->sendUniform("modelMatrix", obj.getModel());
	shader->setVec3("objectColor", obj.getColor());
	shader->setFloat("ambientStrength", obj.getAmbientStrength());
	if (obj.getTexture() >= 0) {
		shader->sendTexture(obj.getTexture());
	}
	obj.makeObject();
}

Renderer::~Renderer()
{
}
