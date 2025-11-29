#pragma once
#include "headers/transform/Transform.hpp"
#include "headers/pch.hpp"

struct Segment
{
    std::vector<glm::vec3> points;
};

class BezierSplineTransform : public Transform
{
private:
    float speed;
    float lastTime;
    float t;

    int currentSegment = 0;
    bool hasEndedPath = false;
    std::vector<Segment> segments;

public:
    BezierSplineTransform(std::vector<glm::vec3> points, float speed);

    glm::mat4 GetTransformMatrix() override;
};
