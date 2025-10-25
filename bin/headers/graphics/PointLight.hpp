#pragma once
#include "headers/interfaces/Subject.hpp"
#include "headers/transform/Transform.hpp"

class PointLight : public Subject
{
private:
    Transform* transform;
    glm::vec3 color;
    float intensity;
    float k_l;
    float k_q;

    void NotifyAll() override;

public:
    PointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q);
    ~PointLight() = default;

    glm::vec3 GetColor();
    glm::vec3 GetPosition();
    float GetLinear();
    float GetQuadratic();

    void SetPosition(glm::vec3 newPosition);
    void Update();
};
