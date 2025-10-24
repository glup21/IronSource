#version 440 core

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

out vec3 fragPos;
out vec3 fragNormal;
out vec3 vertexColor;

uniform mat4 transformMatrix;
uniform mat4 cameraMatrix;

void main()
{
    vec4 worldPos = transformMatrix * vec4(aPos, 1.0);
    fragPos = worldPos.xyz;

    fragNormal = mat3(transpose(inverse(transformMatrix))) * aNormal;

    vertexColor = aColor;

    gl_Position = cameraMatrix * worldPos;
}
