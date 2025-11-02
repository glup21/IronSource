#pragma once
#include "headers/services/ShaderLibrary.hpp"
#include "headers/graphics/PointLight.hpp"
#include "headers/graphics/AmbientLight.hpp"
#include "headers/graphics/DirectionalLight.hpp"
#include "headers/graphics/SpotLight.hpp"

class LightFactory
{
public:
    static PointLight* GetPointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q);
    static AmbientLight* GetAmbientLight(glm::vec3 color, float intensity);
    static DirectionalLight* GetDirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity);
    static SpotLight* GetSpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q, glm::vec3 direction, float cutOff, float outerCutOff);
};