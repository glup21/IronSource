#version 440 core

in vec3 vertexColor;
out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
    fragColor = vec4(1.0);
}
