#version 400

#define MAX_LIGHTS 4 
struct Light
{
	vec3 lightPos;
	vec3 lightColor;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;
uniform float ambientStrength;
uniform sampler2D textureUnitID;
in vec2 uv;
void main()
{
	vec3 result = vec3(0);
	vec3 norm = normalize(Normal);
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	for (int index = 0; index < numberOfLights; index++)
	{
		// ambient
		vec3 ambient = ambientStrength * lights[index].lightColor;
		// diffuse
		vec3 lightDir = normalize(lights[index].lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lights[index].lightColor;
		// specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lights[index].lightColor;
		result += (ambient + diffuse + specular) ;//* objectColor;
		//FragColor =  vec4(index, 0,0, 0);
	}
	FragColor =  vec4(result, 1.0) * texture(textureUnitID, uv);
	//FragColor =  vec4(uv,1, 1);
	//FragColor = vec4(lights[0].lightPos, 1);
};