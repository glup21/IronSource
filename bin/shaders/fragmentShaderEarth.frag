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
uniform sampler2D colorTextures[2];

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

    for (int i = 0; i < numPointLights; i++)
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

    vec4 earthDayColor = texture(colorTextures[0], fragTexCoord);
    vec4 earthNightColor = texture(colorTextures[1], fragTexCoord);

    // Transfer result into brightness for proper blend between textures
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722)) + 0.1;
    // Apply sharp falloff / contrast for day/night terminator
    // This exaggerates the boundary: tweak the exponent for sharper/fuzzier transition
    brightness = pow(clamp(brightness, 0.0, 1.0), 2.0);

    // Blend day and night textures based on sharpFactor
    vec4 texColor = mix(earthNightColor, earthDayColor, brightness);

    fragColor = vec4(texColor.rgb, 1.0);
}
