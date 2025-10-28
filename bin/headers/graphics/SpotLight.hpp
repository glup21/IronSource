#pragma once
#include "headers/graphics/Light.hpp"
#include "headers/transform/Transform.hpp"

class SpotLight : public Light
{
private:
    Transform* transform;
    float k_l;
    float k_q;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    void NotifyAll() override;

public:
    // Replace manual direction with proper Transform 
    SpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q, glm::vec3 direction, float cutOff, float outerCutOff);
    ~SpotLight() = default;

    LightType GetType() const override;
    glm::vec3 GetPosition();
    float GetLinear();
    float GetQuadratic();
    float GetCutOff();
    float GetOuterCutOff();
    glm::vec3 GetDirection();

    void SetPosition(glm::vec3 newPosition);
    void Update();
};
