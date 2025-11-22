#pragma once
#include "headers/transform/Translation.hpp"
#include "headers/pch.hpp"


class DynamicTranslation : public Translation
{
private:
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    float speed;

    float lastTime;
    float t;
    float totalDistance;

public:
    DynamicTranslation(glm::vec3 startPoint, glm::vec3 endPoint, float speed);

    glm::mat4 GetTransformMatrix() override;
};
