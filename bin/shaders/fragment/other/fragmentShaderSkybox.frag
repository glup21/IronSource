#version 440


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
    bool enabled;
    vec3 position;
    vec3 direction;

    vec3 color;
    float intensity;

    float k_l;
    float k_q;

    float cutOff;      
    float outerCutOff; 
};

uniform int numPointLights;
uniform int numAmbientLights;
uniform int numDirectionalLights;
uniform int numSpotLights;

uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform AmbientLight ambientLights[MAX_AMBIENT_LIGHTS];
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform vec3 viewPos;

out vec4 fragColor;
in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
    fragColor = texture(skybox, texCoords);
}