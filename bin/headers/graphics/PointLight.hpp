#pragma once
#include "headers/interfaces/Subject.hpp"
#include "headers/transform/Transform.hpp"

class PointLight : public Subject
{
private:
    Transform* transform;
    glm::vec3 color;   
    float intensity; 

    void NotifyAll() override;
public:
    PointLight(Transform* transform, glm::vec3 color, float intensity);
    ~PointLight() = default;

    glm::vec3 GetColor();
    glm::vec3 GetPosition();

    void SetPosition(glm::vec3 newPosition);

    void Update();
};