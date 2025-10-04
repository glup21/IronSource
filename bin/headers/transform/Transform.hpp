#pragma once

#include "headers/transform/IBasicTransform.hpp"

#include <vector>
#include <glm/mat4x4.hpp> 
#include <memory>

class Transform
{
private:
    std::vector<std::unique_ptr<IBasicTransform>> basicTransforms;

public:
    Transform() = default;
    Transform(std::vector<IBasicTransform*> basicTransforms);
    ~Transform() = default;

    glm::mat4 GetTransformMatrix() const;
    void AddBasicTransform(std::unique_ptr<IBasicTransform> basicTransform);
};