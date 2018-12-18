#include "Shader.h"
#include "Camera.h" 
#include "ShaderLoader.h"

/*const char* vertex_shader =
"#version 400\n"
"layout(location = 0)in vec3 position;"
"layout(location = 1)in vec3 norm;"
"layout(location = 2)in vec2 uv2;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec3 FragPos;"
"out vec3 Normal;"
"out vec2 uv;"
""
"void main()"
"{"
"	FragPos = vec3(modelMatrix * vec4(position, 1.0));"
"	Normal = mat3(transpose(inverse(modelMatrix))) * norm;"
"	gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);"
"	uv = uv2;"
"}";


const char* fragment_shader =
"#version 400\n"
"out vec4 FragColor;"
""
"in vec3 Normal;"
"in vec3 FragPos;"
""
"uniform vec3 lightPos;"
"uniform vec3 viewPos;"
"uniform vec3 lightColor;"
"uniform vec3 objectColor;"
"uniform float ambientStrength;"
"uniform sampler2D textureUnitID;"
"in vec2 uv;"
"void main()"
"{"
"	// ambient \n"

"	vec3 ambient = ambientStrength * lightColor; "
"	// diffuse \n"
"	vec3 norm = normalize(Normal);"
"	vec3 lightDir = normalize(lightPos - FragPos);"
"	float diff = max(dot(norm, lightDir), 0.0);"
"	vec3 diffuse = diff * lightColor;"
"	// specular \n"
"	float specularStrength = 0.5;"
"	vec3 viewDir = normalize(viewPos - FragPos);"
"	vec3 reflectDir = reflect(-lightDir, norm);"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
"	vec3 specular = specularStrength * spec * lightColor;"
""
"	vec3 result = (ambient + diffuse + specular) * objectColor;"
"	FragColor =  vec4(result, 1.0) * texture(textureUnitID, uv);"
//"	FragColor =  vec4(uv, 1, 1);"
"}";*/

Shader::Shader() : Observer() {

}

Shader::Shader(const char* vShader, const char* fShader, Camera *cam) : Observer(cam)
{	
	ShaderLoader *loader = new ShaderLoader();
	this->shaderID = loader->loadShader(vShader, fShader);
	
	//create and compile shaders
	/*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, fragmentShader);
	glAttachShader(shaderID, vertexShader);
	glLinkProgram(shaderID);
	*/

	//tohle
	/*GLint modelMatrixID = glGetUniformLocation(shaderID, "modelMatrix"); //nactu identifikaci z shaderu
	glUseProgram(shaderID);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	sendUniform("modelMatrix", glm::mat4(1.0f));*/

	//ControlOfCompilation();
}

void Shader::useProgram() {
	glUseProgram(this->shaderID);
}

/*bool Shader::ControlOfCompilation() {
	//Kontrola kompilace a linkování program shaderu
	GLint status;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}*/

void Shader::sendUniform(const GLchar *name, glm::mat4 data) {
	GLint uniformID = glGetUniformLocation(this->shaderID, name);
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(data));
	}
	else {
		// in shader doesn't exist uniform variable 
		printf("Shader doesn't exist uniform variable! \n");
	}
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(this->shaderID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->shaderID, name.c_str()), x, y, z);
}
void Shader::setFloat(const std::string &name, float a) const
{
	glUniform1f(glGetUniformLocation(this->shaderID, name.c_str()), a);
}
void Shader::setInt(const std::string &name, int a) const
{
	glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), a);
	//z nevysvetlitelneho duvodu nefunguje
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) {
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, name.c_str()),1,GL_FALSE, &mat[0][0]);
}

void Shader::sendInt(const std::string &name)
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), 0);
}

void Shader::sendTexture(int unitId) {
	GLint uniformID = glGetUniformLocation(shaderID, "textureUnitID");
	glUniform1i(uniformID, unitId);
}

void Shader::sendTexture(const std::string &name, const std::string &number, unsigned int i) {
	glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
}



// clear color and depth buffer
void Shader::clearAndUse(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glUseProgram(this->shaderID);
}

void Shader::update() {
	//printf("update \n");
	sendUniform("projectionMatrix", camera->projectionMatrix);
	sendUniform("viewMatrix", camera->getCamera());
	setVec3("viewPos", camera->getCameraPosition());
}

void Shader::update(glm::mat4 m) {
	//printf("update \n");
	//sendUniform("modelMatrix", m);
}

Shader::~Shader()
{
}
