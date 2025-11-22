#pragma once
#include "headers/pch.hpp"

static const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
static const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);

class IBasicTransform
{
public:
    virtual ~IBasicTransform() = default;

    virtual glm::mat4 GetTransformMatrix() = 0;

};
