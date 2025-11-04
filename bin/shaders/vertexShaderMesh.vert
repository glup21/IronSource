#version 440 core

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    float w = 1.0;
    vec4 worldPos = transformMatrix * vec4(aPos, w);
    fragPos = worldPos.xyz / w;
    fragNormal = normalize(mat3(transpose(inverse(transformMatrix))) * aNormal);
    fragTexCoord = aTexCoord;

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
