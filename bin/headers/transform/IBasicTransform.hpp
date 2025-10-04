#pragma once
#include <glm/glm.hpp>

class IBasicTransform
{
public:
    virtual ~IBasicTransform() = default;

    virtual glm::mat4 GetTransformMatrix() const = 0;
};
