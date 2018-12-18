#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>

#include "Object.h"
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
//#include "ShaderTexture.h"

class Application
{
	float bezX[50];
	float bezY[50];
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f; // yaw do stran, pitch nahoru/dolu
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;
	float cursorX, cursorY;

	bool clicked = false;
	static Application *single;
	Application();

	GLFWwindow* window;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void error_callback(int error, const char* description);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);

	std::vector < Object > objects;
	Renderer* rend;
	Camera camera;
	Shader shader, shader2;
	//ShaderTexture shaderTexture;
	float getPt(float n1, float n2, float perc);
	void getBezier();

public:
	static Application* getInstance();
	bool init(int argc, char* argv[]);
	void callBackFunctions();
	void draw();
	~Application();
};

