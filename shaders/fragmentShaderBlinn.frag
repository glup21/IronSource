#version 440 core

in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertexColor;

#define MAX_LIGHTS 8

uniform int numLights;
uniform vec3 lightPos[MAX_LIGHTS];
uniform vec3 lightColor[MAX_LIGHTS];
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(viewPos - fragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        vec3 L = normalize(lightPos[i] - fragPos);
        vec3 H = normalize(L + V);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), 32.0);

        vec3 diffuse = lightColor[i] * vertexColor * diff;
        vec3 specular = lightColor[i] * spec;

        result += diffuse + specular;
    }

    fragColor = vec4(result, 1.0);
}
