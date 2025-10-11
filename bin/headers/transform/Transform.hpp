#pragma once

#include "headers/transform/IBasicTransform.hpp"

#include <vector>
#include <glm/mat4x4.hpp> 
#include <memory>

// TO DO: Make some broad Transform parameter, that will only change existing Scale, Translation and Rotation, not just add them up
class Transform
{
private:
    // It isnt Composite pattern per se, but I dont want to implement it
    // until I figure out multiple meshes, and how they would relate to each other
    std::vector<std::unique_ptr<IBasicTransform>> basicTransforms;

public:
    Transform() = default;
    Transform(std::vector<IBasicTransform*> basicTransforms);
    ~Transform() = default;

    glm::mat4 GetTransformMatrix();
    void AddBasicTransform(std::unique_ptr<IBasicTransform> basicTransform);
};