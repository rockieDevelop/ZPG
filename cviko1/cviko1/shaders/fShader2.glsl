#version 330 core
out vec4 FragColor;
in vec3 TexCoords;
in vec2 uv2;
uniform vec3 objectColor;
uniform float text;
uniform sampler2D basetexture;
void main()
{    
	if(text==1){
    FragColor =vec4(objectColor,1.0)*texture(basetexture,uv2);
	}
	if(text==0)
	{
		FragColor =vec4(1.0);
	}
}