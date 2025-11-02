#include "headers/services/LightFactory.hpp"

PointLight* LightFactory::GetPointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    PointLight* pointLight = new PointLight(transform, color, intensity, k_l, k_q);
    shaderLibrary.RegisterLight(pointLight);

    return pointLight;
}

AmbientLight* LightFactory::GetAmbientLight(glm::vec3 color, float intensity)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    AmbientLight* ambientLight = new AmbientLight(color, intensity);
    shaderLibrary.RegisterLight(ambientLight);

    return ambientLight;
}

DirectionalLight* LightFactory::GetDirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    DirectionalLight* directionalLight = new DirectionalLight(color, direction, intensity);
    shaderLibrary.RegisterLight(directionalLight);

    return directionalLight;
}

SpotLight* LightFactory::GetSpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q,
    glm::vec3 direction, float cutOff, float outerCutOff)
{
    ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
    SpotLight* spotLight = new SpotLight(transform, color, intensity, k_l, k_q, direction, cutOff, outerCutOff);
    shaderLibrary.RegisterLight(spotLight);

    return spotLight;
}