#include "headers/services/LightFactory.hpp"

LightFactory::LightFactory(ShaderLibrary* shaderLibrary) : shaderLibrary(shaderLibrary)
{

}

std::unique_ptr<PointLight> LightFactory::GetPointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q)
{
    auto pointLight = std::make_unique<PointLight>(transform, color, intensity, k_l, k_q);
    shaderLibrary->RegisterLight(pointLight.get()); 
    pointLightCount++;

    return pointLight; 
}

std::unique_ptr<AmbientLight> LightFactory::GetAmbientLight(glm::vec3 color, float intensity)
{
    auto ambientLight = std::make_unique<AmbientLight>(color, intensity);
    shaderLibrary->RegisterLight(ambientLight.get());
    ambientLightCount++;

    return ambientLight;
}

std::unique_ptr<DirectionalLight> LightFactory::GetDirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity)
{
    auto directionalLight = std::make_unique<DirectionalLight>(color, direction, intensity);
    shaderLibrary->RegisterLight(directionalLight.get());
    directionalLightCount++;

    return directionalLight;
}

std::unique_ptr<SpotLight> LightFactory::GetSpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q,
    glm::vec3 direction, float cutOff, float outerCutOff, std::shared_ptr<Texture> lightTexture)
{
    auto spotLight = std::make_unique<SpotLight>(transform, color, intensity, k_l, k_q, direction, cutOff, outerCutOff, lightTexture);
    shaderLibrary->RegisterLight(spotLight.get());
    spotLightCount++;

    return spotLight;
}

void LightFactory::ResetLightCount()
{
    spotLightCount = 0;
    pointLightCount = 0;
    directionalLightCount = 0;
    ambientLightCount = 0;
}