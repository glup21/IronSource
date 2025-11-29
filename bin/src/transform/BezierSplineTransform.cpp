#include "headers/transform/BezierSplineTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>

BezierSplineTransform::BezierSplineTransform(std::vector<glm::vec3> points, float speed) 
    : speed(speed)
{
    lastTime = glfwGetTime();
    t = 0.0f;

    for(int i = 0; i < points.size(); i += 3)
    {
        int freePoints = points.size() - i;

        if(freePoints < 4)
            break; // Ignore points that cant form a new segment

        std::vector<glm::vec3> segmentPoints = std::vector<glm::vec3>{
            points[i],
            points[i+1],
            points[i+2],
            points[i+3]
        };

        segments.push_back({segmentPoints});
    }
}

glm::mat4 BezierSplineTransform::GetTransformMatrix()
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;


    if(!hasEndedPath)
    {
        t += speed * static_cast<float>(deltaTime);

        while(t >= 1.0f && !hasEndedPath)
        {
            t -= 1.0f;
            currentSegment++;
            if(currentSegment >= segments.size())
            {
                currentSegment = segments.size() - 1;
                hasEndedPath = true;
                t = 1.0f;
            }
        }

        auto points = segments[currentSegment].points;

        currentPos = (float)glm::pow((1 - t), 3) * points[0] +
            3*(float)glm::pow((1 - t), 2) * t * points[1] +
            3*(1 - t) * (t*t) * points[2] + 
            t*t*t * points[3];
    }

    return glm::translate(glm::mat4(1.0f), currentPos);
}
