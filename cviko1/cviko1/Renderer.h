#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <vector>

class Shader;
class Object;
class Renderer
{
private:
	static Renderer *single;
	GLFWwindow* window;

	Renderer(GLFWwindow* win);
public:
	static Renderer* getInstance(GLFWwindow* win);

	void init(void);
	void render(Shader* shader, std::vector<Object> objects);
	void render(Shader* shader, Object obj);
	~Renderer();
};

