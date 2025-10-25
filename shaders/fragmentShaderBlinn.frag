#version 440 core

in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertexColor;

#define MAX_LIGHTS 8

struct PointLight {
    vec3 position;
    vec3 color;
    float k_l; // linear term
    float k_q; // quadratic term
};

uniform int numLights;
uniform PointLight lights[MAX_LIGHTS];
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(viewPos - fragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        vec3 L = normalize(lights[i].position - fragPos);
        vec3 H = normalize(L + V);

        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), 32.0);

        float distance = length(lights[i].position - fragPos);
        float attenuation = 1.0 / (1.0 + lights[i].k_l * distance + lights[i].k_q * distance * distance);
        vec3 diffuse = lights[i].color * vertexColor * diff * attenuation;
        vec3 specular = lights[i].color * spec * attenuation;

        result += diffuse + specular;
    }

    vec3 ambient = vertexColor * 0.1;
    fragColor = vec4(result + ambient, 1.0);
}
