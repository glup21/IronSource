#version 440 core

uniform sampler2D colorTexture;

in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertexColor;

out vec4 fragColor;

void main()
{
    fragColor = vec4(vertexColor.rgb, 1.0);
}
