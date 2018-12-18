#pragma once

#include <vector>
#include "Observer.h"

class Camera
{
private:
	glm::vec3 cameraPos = glm::vec3(10.0f, 10.0f, 20.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	std::vector < Observer * > observers;
	glm::vec3 target;
	//glm::vec3 up;
public:
	//glm::vec3 eye; position
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Camera();
	~Camera();
	void setCamera(void);
	void setCamera(glm::vec3, glm::vec3, glm::vec3);
	void setTargetPosition(glm::vec3);
	void setCameraUp(glm::vec3);
	void setCameraPosition(glm::vec3);
	void setCameraFront(glm::vec3);

	glm::vec3 getCameraPosition(void);
	glm::vec3 getCameraUp(void);
	glm::vec3 getCameraFront(void);
	glm::mat4 getCamera(void);

	void attach(Observer *obs);
	void notify();
};

