#include "Camera.h"

Camera::Camera()
{
	projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::mat4(1.0);
	cameraPos = glm::vec3(10.0f, 7.0f, 20.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::setTargetPosition(glm::vec3 targ) {
	target = targ;
	notify();
}

void Camera::setCameraPosition(glm::vec3 e) {
	cameraPos = e;
	notify();
}

void Camera::setCameraUp(glm::vec3 u) {
	cameraUp = u;
	notify();
}

void Camera::setCamera(void) {
	target = cameraPos + cameraFront;
	viewMatrix = getCamera();
	notify();
}

void Camera::setCamera(glm::vec3 e, glm::vec3 targ, glm::vec3 u) {
	cameraPos = e;
	target = targ;
	cameraUp = u;
	viewMatrix = getCamera();
	notify();
}

void Camera::setCameraFront(glm::vec3 f) {
	cameraFront = f;
}

glm::mat4 Camera::getCamera(void) {
	return glm::lookAt(cameraPos, target, cameraUp);
}

glm::vec3 Camera::getCameraPosition(void) {
	return cameraPos;
}

glm::vec3 Camera::getCameraUp(void) {
	return cameraUp;
}

glm::vec3 Camera::getCameraFront(void) {
	return cameraFront;
}




void Camera::attach(Observer *obs) {
	observers.push_back(obs);
}
void Camera::notify() {
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->update();
	}
	//printf("number of observers %d \n", observers.size());
}

Camera::~Camera()
{
}
