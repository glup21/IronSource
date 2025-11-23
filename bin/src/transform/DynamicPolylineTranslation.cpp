#include "headers/transform/DynamicPolylineTranslation.hpp"
#include <glm/gtc/matrix_transform.hpp>

DynamicPolylineTranslation::DynamicPolylineTranslation(std::vector<glm::vec3> points, float speed) 
    : Translation(points.size() == 0 ? glm::vec3(0.0f) : points[0]), points(points), speed(speed)
{
    lastTime = glfwGetTime();
    t = 0.0f;
    totalLength = 0.0f;

    segmentLengths.clear();
    for (int i = 0; i < points.size() - 1; i++)
    {
        float len = glm::length(points[i + 1] - points[i]);
        segmentLengths.push_back(len);
        totalLength += len;
    }
}

glm::mat4 DynamicPolylineTranslation::GetTransformMatrix()
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (totalLength <= 0.0f)
    {
        t = 1.0f;
    }
    else
    {
        t += (speed * static_cast<float>(deltaTime)) / totalLength;
        t = glm::clamp(t, 0.0f, 1.0f);
    }

    float distanceAlong = t * totalLength;
    glm::vec3 currentPos = points[0];
    float accumulated = 0.0f;

    for (int i = 0; i < segmentLengths.size(); i++)
    {
        if (accumulated + segmentLengths[i] >= distanceAlong)
        {
            float localTranslation = (distanceAlong - accumulated) / segmentLengths[i];
            currentPos = glm::mix(points[i], points[i + 1], localTranslation);
            break;
        }
        accumulated += segmentLengths[i];
    }

    return glm::translate(glm::mat4(1.0f), currentPos);
}
