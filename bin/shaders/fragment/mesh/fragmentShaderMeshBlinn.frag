#version 440 core

#define MAX_POINT_LIGHTS 32
#define MAX_AMBIENT_LIGHTS 32
#define MAX_DIRECTIONAL_LIGHTS 32
#define MAX_SPOT_LIGHTS 32

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
    vec2 attenuation;
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

    vec2 attenuation;

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
uniform sampler2D normalTexture;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

in vec3 fragNormal;
in vec3 fragPos;
in vec2 fragTexCoord;

out vec4 fragColor;

void main()
{

    vec3 N = normalize(fragNormal);
    vec3 V = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0);

    for (int i = 0; i < numAmbientLights; i++)
    {
        AmbientLight light = ambientLights[i];
        result += light.color * light.intensity * materialAmbient;
    }

    for (int i = 0; i < numPointLights; i++)
    {
        PointLight light = pointLights[i];

        vec3 N = normalize(fragNormal);
        vec3 L = normalize(light.position - fragPos);
        vec3 V = normalize(viewPos - fragPos);
        vec3 H = normalize(L + V);
        float diff = max(dot(N, L), 0.0);

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (1.0 + light.attenuation.x * distance + light.attenuation.y * distance * distance);

        vec3 diffuse = diff * light.color * light.intensity * attenuation * materialDiffuse;
        vec3 specular = vec3(0.0f); 
        if(diff > 0.0f)
        {
            float spec = pow(max(dot(V, H), 0.0), materialShininess);
            specular = spec * light.color * attenuation  * materialSpecular;
        } 

        result += diffuse + specular;
    }

    for (int i = 0; i < numDirectionalLights; i++)
    {
        DirectionalLight light = directionalLights[i];

        vec3 L = normalize(-light.direction);

        float diff = max(dot(N, L), 0.0);           
        vec3 H = normalize(L + V);                 
        float spec = pow(max(dot(N, H), 0.0), materialShininess);

        vec3 diffuse = diff * light.color * light.intensity* materialDiffuse;
        vec3 specular = spec * light.color  * materialSpecular * 0.1;

        result += diffuse + specular;
    }

    for (int i = 0; i < numSpotLights; i++)
    {
        SpotLight light = spotLights[i];
        if(light.enabled)
        {
            vec3 L = normalize(light.position - fragPos);
            float diff = max(dot(N, L), 0.0);
            vec3 H = normalize(L + V);
            float spec = pow(max(dot(N, H), 0.0), materialShininess);

            float distance = length(light.position - fragPos);
            float attenuation = 1.0 / (1.0 + light.attenuation.x * distance + light.attenuation.y * distance * distance);

            float dotLF = dot(normalize(-L), normalize(light.direction));

            if(dotLF > light.outerCutOff)
            {
                // Normalization Formula xn = ( x - Min )/( Max - Min )
                float intensityFactor = (dotLF - light.outerCutOff)/(light.cutOff - light.outerCutOff );

                vec3 diffuse = diff * light.color * light.intensity * attenuation * materialDiffuse * intensityFactor;
                vec3 specular = spec * light.color  * attenuation * materialSpecular * intensityFactor;

                result += diffuse + specular;
            }
        }
    }

    vec4 texColor = texture(colorTexture, fragTexCoord);
    fragColor = vec4(result * texColor.rgb, texColor.a);
}
