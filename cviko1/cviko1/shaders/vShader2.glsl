#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 2) in vec2 uv;

out vec2 uv2;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	uv2=uv;
	gl_Position = projectionMatrix* viewMatrix* modelMatrix* vec4(aPos, 1.0);
}