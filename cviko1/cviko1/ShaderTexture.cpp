#include "ShaderTexture.h"
#include "Camera.h" 

const char* vertex_shader2 =
"#version 330 core "
"layout(location = 0) in vec3 aPos;"
"layout(location = 1) in vec2 aTexCoord;"

"out vec2 TexCoord;"

"void main()"
"{"
"	gl_Position = vec4(aPos, 1.0);"
"	TexCoord = aTexCoord;"
"}";

const char* fragment_shader2 =
"#version 330 core "
"out vec4 FragColor;"

"in vec2 TexCoord;"

"uniform sampler2D ourTexture;"

"void main()"
"{"
"	FragColor = texture(ourTexture, TexCoord);"
"}";

ShaderTexture::ShaderTexture() : Shader() {

}

/*ShaderTexture::ShaderTexture(Camera *cam) : Shader(cam)
{
	//create and compile shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader2, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader2, NULL);
	glCompileShader(fragmentShader);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, fragmentShader);
	glAttachShader(shaderID, vertexShader);
	glLinkProgram(shaderID);

	GLint modelMatrixID = glGetUniformLocation(shaderID, "modelMatrix"); //nactu identifikaci z shaderu
	glUseProgram(shaderID);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	sendUniform("modelMatrix", glm::mat4(1.0f));

	ControlOfCompilation();
}*/

bool ShaderTexture::ControlOfCompilation(void)
{
	//Kontrola kompilace a linkování program shaderu
	GLint status;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "TextureShader linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}

void ShaderTexture::sendUniform(const GLchar * name, glm::mat4 data)
{
	GLint uniformID = glGetUniformLocation(this->shaderID, name);
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(data));
	}
	else {
		// in shader doesn't exist uniform variable 
		printf("TextureShader doesn't exist uniform variable! \n");
	}
}


void ShaderTexture::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(this->shaderID, name.c_str()), 1, &value[0]);
}
void ShaderTexture::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->shaderID, name.c_str()), x, y, z);
}
void ShaderTexture::sendInt(const std::string & name, GLuint * value)
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), *value);
}

void ShaderTexture::clearAndUse(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(this->shaderID);
}

void ShaderTexture::update()
{
	sendUniform("projectionMatrix", camera->projectionMatrix);
	sendUniform("viewMatrix", camera->getCamera());
	setVec3("viewPos", camera->getCameraPosition());
}

void ShaderTexture::update(glm::mat4 m) {

}


ShaderTexture::~ShaderTexture()
{
}
