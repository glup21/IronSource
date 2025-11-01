#version 440 core

in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertexColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 fragColor;

void main()
{
    // Normalize vectors
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);

    // Diffuse lighting
    float diff = max(dot(N, L), 0.0);

    // Combine light and vertex color
    vec3 result = lightColor * vertexColor * diff;

    fragColor = vec4(result, 1.0);
}
