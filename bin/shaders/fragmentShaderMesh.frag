#version 440 core

#define MAX_POINT_LIGHTS 8
#define MAX_AMBIENT_LIGHTS 8
#define MAX_DIRECTIONAL_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

struct AmbientLight
{
    vec3 color;
    float intensity;
};

struct PointLight
{
    vec3 color;
    float intensity;

    vec3 position;
    float k_l;

    float k_q;
};

struct DirectionalLight
{
    vec3 color;
    float intensity;
    vec3 direction; 
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 color;
    float intensity;

    float k_l;
    float k_q;

    float cutOff;      
    float outerCutOff; 
};

// Lights number
uniform int numPointLights;
uniform int numAmbientLights;
uniform int numDirectionalLights;
uniform int numSpotLights;

// Light arrays
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform AmbientLight ambientLights[MAX_AMBIENT_LIGHTS];
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform vec3 viewPos;
uniform sampler2D colorTexture;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShinnines;

in vec3 fragNormal;
in vec3 fragPos;
in vec2 fragTexCoord;

out vec4 fragColor;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0);

    for (int i = 0; i < MAX_AMBIENT_LIGHTS; i++)
    {
        AmbientLight light = ambientLights[i];
        result += light.color * light.intensity * materialAmbient;
    }

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        PointLight light = pointLights[i];

        vec3 L = normalize(light.position - fragPos);
        float diff = max(dot(N, L), 0.0);
        vec3 H = normalize(L + V);
        float spec = pow(max(dot(N, H), 0.0), materialShinnines);

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (1.0 + light.k_l * distance + light.k_q * distance * distance);

        vec3 diffuse = diff * light.color * light.intensity * attenuation * materialDiffuse;
        vec3 specular = spec * light.color * 0.5 * attenuation * materialSpecular;

        result += diffuse + specular;
    }

    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
    {
        DirectionalLight light = directionalLights[i];

        vec3 L = normalize(-light.direction);

        float diff = max(dot(N, L), 0.0);           
        vec3 H = normalize(L + V);                 
        float spec = pow(max(dot(N, H), 0.0), materialShinnines);

        vec3 diffuse = diff * light.color * light.intensity* materialDiffuse;
        vec3 specular = spec * light.color * 0.5 * materialSpecular;

        result += diffuse + specular;
    }

    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        SpotLight light = spotLights[i];

        vec3 L = normalize(light.position - fragPos);
        float diff = max(dot(N, L), 0.0);
        vec3 H = normalize(L + V);
        float spec = pow(max(dot(N, H), 0.0), materialShinnines);

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (1.0 + light.k_l * distance + light.k_q * distance * distance);

        float theta = dot(normalize(-light.direction), L);
        float epsilon = light.cutOff - light.outerCutOff;
        float intensityFactor = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 diffuse = diff * light.color * light.intensity * attenuation * materialDiffuse * intensityFactor;
        vec3 specular = spec * light.color * 0.5 * attenuation * materialSpecular;

        result += diffuse + specular;
    }

    vec4 texColor = texture(colorTexture, fragTexCoord);
    fragColor = vec4(result * texColor.rgb, 1.0);
}
