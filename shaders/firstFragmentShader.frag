#version 440 core

in vec3 inputColor;
out vec4 fragColor;

void main()
{
    fragColor = vec4(inputColor.r, inputColor.g, inputColor.b, 1.0);
}
