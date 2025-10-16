#pragma once
#include "headers/interfaces/Subject.hpp"
#include "headers/transform/Transform.hpp"

class PointLight : public Subject
{
private:
    std::unique_ptr<Transform> transform;
    glm::vec3 color;   
    float intensity; 

    void NotifyAll() override;
public:
    PointLight(Transform transform, glm::vec3 color, float intensity);
    ~PointLight() = default;

    void Update();
};