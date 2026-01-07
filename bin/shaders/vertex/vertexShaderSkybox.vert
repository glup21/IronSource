#version 440 core
layout(location = 0) in vec3 aPos;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform float w;

out vec3 texCoords;

void main()
{
    texCoords = aPos;

    vec4 pos = projectionMatrix * viewMatrix * vec4(aPos * w, w);
    gl_Position = pos;

}