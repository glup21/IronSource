#pragma once
#include "headers/transform/Rotation.hpp"
#include <GLFW/glfw3.h> 

class DynamicRotation : public Rotation
{
private:
    float rotationSpeed;   
    mutable double lastTime; 

public:
    DynamicRotation(glm::vec3 startAngles, float rotationSpeed);

    glm::mat4 GetTransformMatrix() override;
};
