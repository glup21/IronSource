#include "headers/transform/Rotation.hpp"

Rotation::Rotation(float angle, glm::vec3 axis) : angle(angle), axis(axis) {}

void Rotation::SetAngle(float angle)
{
    this->angle = angle;
}

float Rotation::GetAngle() 
{
    return angle;
}

void Rotation::SetAxis(glm::vec3 axis)
{
    this->axis = axis;
}

glm::vec3 Rotation::GetAxis() 
{
    return axis;
}

glm::mat4 Rotation::GetTransformMatrix()
{
    return glm::rotate(glm::mat4(1.0f), angle, axis);
}
