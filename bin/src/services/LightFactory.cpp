#include "headers/services/LightFactory.hpp"

PointLight* LightFactory::GetPointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    PointLight* pointLight = new PointLight(transform, color, intensity, k_l, k_q);
    shaderLibrary.RegisterLight(pointLight);

    pointLightCount++;
    return pointLight;
}

AmbientLight* LightFactory::GetAmbientLight(glm::vec3 color, float intensity)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    AmbientLight* ambientLight = new AmbientLight(color, intensity);
    shaderLibrary.RegisterLight(ambientLight);

    ambientLightCount++;
    return ambientLight;
}

DirectionalLight* LightFactory::GetDirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    DirectionalLight* directionalLight = new DirectionalLight(color, direction, intensity);
    shaderLibrary.RegisterLight(directionalLight);

    directionalLightCount++;
    return directionalLight;
}

SpotLight* LightFactory::GetSpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q,
    glm::vec3 direction, float cutOff, float outerCutOff, std::shared_ptr<Texture> lightTexture)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    SpotLight* spotLight = new SpotLight(transform, color, intensity, k_l, k_q, direction, cutOff, outerCutOff, lightTexture);
    shaderLibrary.RegisterLight(spotLight);

    spotLightCount++;
    return spotLight;
}