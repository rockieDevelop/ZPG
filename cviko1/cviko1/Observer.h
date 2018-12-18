#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Camera;
class Observer {
	// 2. "dependent" functionality
protected:
	Camera *camera;
public:
	Observer();
	Observer(Camera *cam);
	virtual void update() = 0;
	virtual void update(glm::mat4) = 0;
protected:
	Camera *getSubject();
};
