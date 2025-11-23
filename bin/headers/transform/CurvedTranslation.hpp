#pragma once
#include "headers/transform/Translation.hpp"
#include "headers/pch.hpp"

const int CLOCKWISE = -1;
const int COUNTER_CLOCKWISE = 1;

class CurvedTranslation : public Translation
{
private:
    float radius;
    float speed;

    float lastTime;
    float currentAngle;
    glm::vec3 startPoint;
    int direction;
    
public:
    CurvedTranslation(glm::vec3 startPoint, float radius, float speed, int direction = CLOCKWISE);

    glm::mat4 GetTransformMatrix() override;
};
