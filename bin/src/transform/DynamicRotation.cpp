#include "headers/transform/DynamicRotation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>
DynamicRotation::DynamicRotation(float angle, glm::vec3 axis, float rotationSpeed)
    : Rotation(angle, axis), rotationSpeed(rotationSpeed)
{
    lastTime = glfwGetTime();
}

glm::mat4 DynamicRotation::GetTransformMatrix() 
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    angle += rotationSpeed * static_cast<float>(deltaTime);

    return glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis));
}
