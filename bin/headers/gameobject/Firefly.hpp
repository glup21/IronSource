#pragma once
#include "headers/gameobject/GameObject.hpp"
#include "headers/graphics/PointLight.hpp"

class Firefly : GameObject
{
private:
    int distance;
    std::shared_ptr<PointLight> light;
public:
    Firefly(Transform* transform, int distance, glm::vec3 color, float intensity, float k_l, float k_q);
    ~Firefly() = default;

    void Update() override;
}; 