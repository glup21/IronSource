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

    if (totalDistance <= 0.0f)
    {
        t = 1.0f;
    }
    else
    {
        t += (speed * static_cast<float>(deltaTime)) / totalDistance;
        if (t > 1.0f) t = 1.0f;
        if (t < 0.0f) t = 0.0f;
    }

    glm::vec3 currentPos = startPoint + t * (endPoint - startPoint);

    return glm::translate(glm::mat4(1.0f), currentPos);
}
