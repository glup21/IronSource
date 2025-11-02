#pragma once
#include "headers/transform/Rotation.hpp"
#include "headers/pch.hpp"


class DynamicRotation : public Rotation
{
private:
    float rotationSpeed;   
    mutable double lastTime; 

public:
    DynamicRotation(glm::vec3 startAngles, float rotationSpeed);

    glm::mat4 GetTransformMatrix() override;
};
