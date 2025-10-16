#version 440 core

in vec3 fragNormal;
in vec3 fragPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 fragColor;

void main()
{
    // Normalize vectors
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);

    // Diffuse term
    float diff = max(dot(N, L), 0.0);

    vec3 result = lightColor * objectColor * diff;
    fragColor = vec4(result, 1.0);
}
