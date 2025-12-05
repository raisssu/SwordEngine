#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;


uniform vec3 objectColor;
uniform vec3 lightColor;


uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
	

	FragColor = vec4(result, 0.4) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8);
};