#version 440 core

in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertexColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);
    vec3 V = normalize(viewPos - fragPos);
    vec3 R = reflect(-L, N);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(V, R), 0.0), 32.0);

    vec3 diffuse = lightColor * vertexColor * diff;
    vec3 specular = lightColor * spec;

    vec3 result = diffuse + specular;
    fragColor = vec4(result, 1.0);
}
