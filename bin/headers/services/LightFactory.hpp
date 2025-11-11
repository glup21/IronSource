#pragma once
#include "headers/services/ShaderLibrary.hpp"
#include "headers/graphics/PointLight.hpp"
#include "headers/graphics/AmbientLight.hpp"
#include "headers/graphics/DirectionalLight.hpp"
#include "headers/graphics/SpotLight.hpp"

class LightFactory
{
public:
    static LightFactory& GetInstance()
    {
        static LightFactory instance;
        return instance;
    }
    PointLight* GetPointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q);
    AmbientLight* GetAmbientLight(glm::vec3 color, float intensity);
    DirectionalLight* GetDirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity);
    SpotLight* GetSpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q, glm::vec3 direction, float cutOff, float outerCutOff);

    int pointLightCount = 0;
    int ambientLightCount = 0;
    int directionalLightCount = 0;
    int spotLightCount = 0;
};