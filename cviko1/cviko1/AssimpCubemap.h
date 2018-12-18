#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW 
#include <GLFW/glfw3.h>
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <soil.h>
#include <stdio.h>
#include "Observer.h"
#include <string.h>
#include <iostream>
#include "stb_image.h"


class AssimpCubemap
{
private:
	unsigned int cubemapTexture;
	unsigned int VAO;
	unsigned int VBO;
public:
	AssimpCubemap();
	~AssimpCubemap();
	void CreateCube();
	void setSkyBox();
};

