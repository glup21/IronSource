#pragma once
#include "headers/graphics/Light.hpp"
#include "headers/transform/Transform.hpp"

class PointLight : public Light
{
private:
    Transform* transform;
    float k_l;
    float k_q;

    void NotifyAll() override;

public:
    PointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q);
    ~PointLight() = default;

    LightType GetType() const override;
    glm::vec3 GetPosition();
    float GetLinear();
    float GetQuadratic();

    void SetPosition(glm::vec3 newPosition);
    void Update();
};
