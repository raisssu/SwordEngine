#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
//in vec3 Normal;
//in vec3 FragPos;
in vec3 LightingColor;

uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	
	FragColor = vec4(LightingColor * objectColor, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8);
};