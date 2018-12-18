#include "Application.h"

#include "MySphere.h"
#include "Suzi.h"
#include "Light.h"
#include "Plain.h"
#include "Texture.h"
#include "Model.h"
#include "AssimpCubemap.h"

#include <soil.h>
#include <math.h>

Application* Application::single = NULL;

Application* Application::getInstance()
{
	if (single == NULL)
	{
		single = new Application();
		return single;
	}
	return single;

}

Application::Application()
{
	printf("Application \n");
}

void Application::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	/*if (key == GLFW_KEY_W)
		cameraPos += cameraSpeed * cameraFront;
	if (key == GLFW_KEY_S)
		cameraPos -= cameraSpeed * cameraFront;
	if (key == GLFW_KEY_A)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (key == GLFW_KEY_D)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);
	cursorX = mouseX;
	cursorY = mouseY;
	if (clicked) {

		if (firstMouse) // this bool variable is initially set to true
		{
			lastX = cursorX;
			lastY = cursorY;
			firstMouse = false;
		}

		float xoffset = lastX - cursorX;
		float yoffset = lastY - cursorY;
		lastX = cursorX;
		lastY = cursorY;
		float sensitivity = 0.15f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw -= xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		camera.setCameraFront(glm::normalize(front));
	}
	else {
		lastX = cursorX;
		lastY = cursorY;
		firstMouse = true;
	}
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	printf("mouse_button_callback %d, %d, %d \n", button, action, mods);
	if (action == 1) {
		//naètení ID a pozice ve svìtových souøadnicích
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)cursorX;
		GLint y = (GLint)cursorY;

		int newy = 600 - y;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

		//Application::getInstance()->getScene()->getRenderer()->setSelect(index-1);

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4& view = camera.viewMatrix;
		glm::mat4& projection = camera.projectionMatrix;

		glm::vec4& viewPort = glm::vec4(0, 0,
			800,
			600);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		printf("unProject[%f, %f, %f]\n", pos.x, pos.y, pos.z);
		if (button == 1) {
			Model cube = Model(&shader, 2);
			cube.setPosition(glm::vec3(pos.x, pos.y, pos.z));
			cube.load("./Models/Tree 02/Tree.obj");
			cube.setTexture(3);
			objects.push_back(cube);
		}
		else {
			clicked = true;
		}
	}
	else clicked = false;
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback %d \n", focused);
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback %d \n", iconified);
}

bool Application::init(int argc, char* argv[])
{
	printf(" Application::init \n");

	//
	if (!glfwInit()) {
		return false;
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	return true;
}

void Application::callBackFunctions() {

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });

	glfwSetErrorCallback([](int error, const char* description) -> void {Application::getInstance()->error_callback(error, description); });

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Application::getInstance()->window_size_callback(window, width, height); });

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void {Application::getInstance()->mouse_button_callback(window, button, action, mods); });

	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) -> void {Application::getInstance()->window_focus_callback(window, focused); });

	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) -> void {Application::getInstance()->window_iconify_callback(window, iconified); });


}


void Application::draw() {
	
	rend = rend->getInstance(window);
	rend->init();
	
	camera = Camera();
	shader = Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl", &camera);
	shader.useProgram();
	//shader2 = Shader("./shaders/vShader2.glsl", "./shaders/fShader2.glsl", &camera);
	//shaderTexture = ShaderTexture(&camera);

	//MySphere object = MySphere(&shader, 1);
	//MySphere object2 = MySphere(&shader,2);
	//Suzi object3 = Suzi(&shader,3);
	//Suzi object4 = Suzi(&shader,4);

	float radius = 14.0f;
	float lX = sin(glfwGetTime()) * radius;
	float lZ = cos(glfwGetTime()) * radius;
	Light light = Light(&shader, 10, 0);
	Light light1 = Light(&shader, 11, 1);
	Light light2 = Light(&shader, 12, 2);
	light.setColor(glm::vec3(1.0, 1.0, 1.0));
	light.setPosition(glm::vec3(lX, 1.0, lZ));
	light1.setColor(glm::vec3(1.0, 1.0, 1.0));
	light1.setPosition(glm::vec3(0, 5, 0));
	light2.setColor(glm::vec3(1.0, 1.0, 1.0));
	light2.setPosition(glm::vec3(0, lX, lZ));

	//AssimpCubemap skybox = AssimpCubemap();
	//skybox.setSkyBox();
	//shader2.useProgram();
	//shader2.setInt("skybox",0);
	//shader2.setMat4("viewMatrix", camera.viewMatrix);
	//shader2.setMat4("projectionMatrix", camera.projectionMatrix);
	//skybox.CreateCube();


	Texture t1 = Texture();
	GLuint textureID = SOIL_load_OGL_texture("./Models/test.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	GLuint textureID2 = SOIL_load_OGL_texture("./sky/skydome.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	GLuint textureLight = SOIL_load_OGL_texture("./Models/white.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	GLuint texturePlant = SOIL_load_OGL_texture("./Models/Tree 02/DB2X2_L01.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	GLuint textureGrass = SOIL_load_OGL_texture("./Models/grass/grass.jpg", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	t1.setTextureUnit(textureID, 0); //do jednotky 0 ulozim dum
	t1.setTextureUnit(textureID2, 1); //do jednotky 1 ulozim skydome
	t1.setTextureUnit(textureLight, 2);
	t1.setTextureUnit(texturePlant, 3);
	t1.setTextureUnit(textureGrass, 4);

	Model house = Model(&shader, 1);
	house.setPosition(glm::vec3(0.0, 0.0, 0.0));
	house.load("./Models/test.obj");
	house.setTexture(0); //nastavuju jednotku 0 pro vykresleni domu
	objects.push_back(house);

	Model cube = Model(&shader, 2);
	cube.setPosition(glm::vec3(10.0, 0.0, 0.0));
	cube.load("./Models/Tree 02/Tree.obj");
	cube.setTexture(3);
	objects.push_back(cube);

	Model ground = Model(&shader, 3);
	ground.setPosition(glm::vec3(0.0, -8.2, 0.0));
	ground.rotate(4.72, 1.0, 0.0, 0.0);
	ground.load("./Models/grass/grass.obj");
	ground.setTexture(4);
	objects.push_back(ground);

	Model skydom = Model(&shader, 20);
	skydom.setPosition(glm::vec3(0.0, 0.0, 0.0));
	skydom.scale(glm::vec3(10.0,10.0,10.0));
	skydom.load("./sky/skydome.obj");
	skydom.setTexture(1);
	objects.push_back(skydom);

	light.setTexture(2);
	light1.setTexture(2);
	light2.setTexture(2);
	
	
	float r = 0;
	camera.setCamera();
	shader.setInt("numberOfLights", 3);
	getBezier();
	int i = 0;
	bool up = true;
	while (!glfwWindowShouldClose(window))
	{
		shader.clearAndUse();
		float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.setCameraPosition(camera.getCameraPosition() + (cameraSpeed * camera.getCameraFront()));
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.setCameraPosition(camera.getCameraPosition() - (cameraSpeed * camera.getCameraFront()));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.setCameraPosition(camera.getCameraPosition() - (glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * cameraSpeed));
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.setCameraPosition(camera.getCameraPosition() + (glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * cameraSpeed));

		//r += 0.002;
		//printf("r%f ", r);
		//objects[2].rotate(0.002, 1.0, 0.0, 0.0);

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		for (Object obj : objects) {
			glStencilFunc(GL_ALWAYS, obj.getID(), 0xFF);
			rend->render(&shader, obj);
			//shader.sendInt("");
		}	
		glStencilFunc(GL_ALWAYS, light.getID(), 0xFF);
		//glStencilFunc(GL_ALWAYS, light1.getID(), 0xFF);
		//glStencilFunc(GL_ALWAYS, light2.getID(), 0xFF);
		//plain.bindTexture(texToSend);
		
		rend->render(&shader, light);
		rend->render(&shader, light1);
		rend->render(&shader, light2);

		//rend->render(&shader, plain);

		lX = sin(glfwGetTime()) * radius;
		lZ = cos(glfwGetTime()) * radius;
		light.setPosition(glm::vec3(lX, 1.0f, lZ));
		light2.setPosition(glm::vec3(bezX[i], bezY[i], 10));
		if (i >= 49)
			up = false;
		if (i <= 0)
			up = true;
		if (up)
			i++;
		else
			i--;
		

		camera.setCamera();

		//rend->render(&shader, objects);
		rend->render(&shader, light);

		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);
	glfwTerminate();
}


Application::~Application()
{
	printf("Destructor ~Application \n");
}

void Application::getBezier() {
	float xa, xb, ya, yb, x, y;
	for (float i = 0; i < 1; i += 0.02)
	{
		// The Green Line
		xa = getPt(-7, -2, i);//x1,x2
		ya = getPt(8, 15, i);//y1,y2
		xb = getPt(-2, 10, i);//x2,x3
		yb = getPt(15, 7, i);//y2,y3

		// The Black Dot
		x = getPt(xa, xb, i);
		y = getPt(ya, yb, i);
		int i2 = i * 50;
		bezX[i2] = x;
		bezY[i2] = y;
	}
}

float Application::getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;

	return n1 + (diff * perc);
}