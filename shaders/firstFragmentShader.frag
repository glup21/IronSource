#version 440 core

in vec3 inputColor;
out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
    fragColor = vec4(inputColor.r, inputColor.g, inputColor.b, 1.0);
}