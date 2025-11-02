#pragma once
#include "headers/pch.hpp"


class IBasicTransform
{
public:
    virtual ~IBasicTransform() = default;

    virtual glm::mat4 GetTransformMatrix() = 0;

};
