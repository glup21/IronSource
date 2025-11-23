#pragma once
#include "headers/transform/Translation.hpp"
#include "headers/pch.hpp"
#include <vector>

class DynamicPolylineTranslation : public Translation
{
private:
    std::vector<glm::vec3> points;
    float speed;

    float lastTime;
    float t;
    float totalLength;
    std::vector<float> segmentLengths;

public:
    DynamicPolylineTranslation(std::vector<glm::vec3> points, float speed);

    glm::mat4 GetTransformMatrix() override;
};
