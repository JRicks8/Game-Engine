#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	vec3 norm = normalize(Normal);
	
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
}