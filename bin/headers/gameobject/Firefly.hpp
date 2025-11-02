#pragma once
#include "headers/gameobject/GameObject.hpp"
#include "headers/graphics/PointLight.hpp"
#include <optional>

class Firefly : public GameObject
{
private:
    float distance;
    std::shared_ptr<PointLight> light;
    float speed;

    bool reachedDestination = false;
    std::optional<glm::vec3> destination;
public:
    Firefly(Transform* transform, float distance, glm::vec3 color, float intensity, float k_l, float k_q, float speed, ShaderLibrary* shaderLibrary,
        std::string vertexShader, std::string fragmentShader);
    ~Firefly() = default;

    void Update(float deltaTime) override;
    void SetNewDestination();
}; 