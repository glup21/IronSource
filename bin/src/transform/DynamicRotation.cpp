#include "headers/transform/DynamicRotation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>
DynamicRotation::DynamicRotation(glm::vec3 startAngles, float rotationSpeed)
    : Rotation(startAngles), rotationSpeed(rotationSpeed)
{
    lastTime = glfwGetTime();
}

glm::mat4 DynamicRotation::GetTransformMatrix() 
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    angles.y += rotationSpeed * static_cast<float>(deltaTime);

    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), angles.x, glm::vec3(1,0,0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), angles.y, glm::vec3(0,1,0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), angles.z, glm::vec3(0,0,1));

    return rotZ * rotY * rotX;
}
