#pragma once
#include "headers/graphics/Light.hpp"
#include "headers/transform/Transform.hpp"

class AmbientLight : public Light
{
private:
    void NotifyAll() override;

public:
    AmbientLight(glm::vec3 color, float intensity);
    ~AmbientLight() = default;

    LightType GetType() const override;

    void Update();
};
