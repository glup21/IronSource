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
    vec4 texColor = texture(colorTexture, fragTexCoord);
    fragColor = vec4(texColor.rgb, 1.0);
}
