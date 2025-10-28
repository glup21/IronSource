#pragma once
#include "headers/graphics/Light.hpp"
#include "headers/transform/Transform.hpp"

class DirectionalLight : public Light
{
private:
    glm::vec3 direction;

    void NotifyAll() override;

public:
    DirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity);
    ~DirectionalLight() = default;

    LightType GetType() const override;
    glm::vec3 GetDirection();

    void Update();
};
