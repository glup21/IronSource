#include "headers/transform/Rotation.hpp"

Rotation::Rotation(glm::vec3 angles) : angles(angles) {}

void Rotation::SetAngles(glm::vec3 angles) 
{
    angles = angles;
}

glm::vec3 Rotation::GetAngles() const 
{ 
    return angles;
}

glm::mat4 Rotation::GetTransformMatrix() 
{
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), angles.x, glm::vec3(1,0,0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), angles.y, glm::vec3(0,1,0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), angles.z, glm::vec3(0,0,1));
    return rotZ * rotY * rotX;
}
