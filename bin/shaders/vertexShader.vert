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
    float w = 1.0;
    vec4 worldPos = transformMatrix * vec4(aPos, w);
    fragPos = worldPos.xyz / w;

    fragNormal = normalize(mat3(transpose(inverse(transformMatrix))) * aNormal);

    vertexColor = aColor;

    gl_Position = cameraMatrix * worldPos;
}
