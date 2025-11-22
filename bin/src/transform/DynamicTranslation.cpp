#include "headers/transform/DynamicTranslation.hpp"
#include <glm/gtc/matrix_transform.hpp>

DynamicTranslation::DynamicTranslation(glm::vec3 startPoint, glm::vec3 endPoint, float speed) 
    : Translation(startPoint), startPoint(startPoint), endPoint(endPoint), speed(speed)
{
    lastTime = glfwGetTime();
    t = 0.0f;
    totalDistance = glm::length(endPoint - startPoint);
}

glm::mat4 DynamicTranslation::GetTransformMatrix()
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    t += speed * static_cast<float>(deltaTime);

    if (t * totalDistance > totalDistance) t = 1.0f;

    glm::vec3 currentPos = startPoint + t * (endPoint - startPoint);

    return glm::translate(glm::mat4(1.0f), currentPos);
}
