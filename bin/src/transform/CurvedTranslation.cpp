#include "headers/transform/CurvedTranslation.hpp"
#include <glm/gtc/matrix_transform.hpp>

CurvedTranslation::CurvedTranslation(glm::vec3 startPoint, float radius, float speed, int direction) 
    : Translation(startPoint), startPoint(startPoint), radius(radius), speed(speed), direction(direction)
{
    lastTime = glfwGetTime();
    currentAngle = 0.0f;
}

glm::mat4 CurvedTranslation::GetTransformMatrix()
{
    glm::vec3 currentPos;
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    currentAngle += speed * static_cast<float>(deltaTime);

    if (currentAngle > glm::two_pi<float>())
        currentAngle -= glm::two_pi<float>();

    currentPos.x = startPoint.x + cos(currentAngle);
    currentPos.y = startPoint.y + sin(currentAngle);
    
    currentPos.x *= direction;

    return glm::translate(glm::mat4(1.0f), currentPos);
}
