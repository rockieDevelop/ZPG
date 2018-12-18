#include "Observer.h"
#include "Camera.h"

Observer::Observer() {

}

Observer::Observer(Camera *cam) {
	camera = cam;
	// 4. Observers register themselves with the Subject
	camera->attach(this);
}

Camera *Observer::getSubject() {
	return camera;
}
