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

    float time = 1.0f;
    glm::vec3 currentPos;
    if(!hasEndedPath)
    {
        t += (speed * static_cast<float>(deltaTime)) / time;
        if(t >= 1.0f)
        {
            t = 0.0f;
            currentSegment++;
            if(currentSegment >= segments.size())
            {
                hasEndedPath = true;
                currentSegment = segments.size() - 1;
            }
            
        }
        //t = glm::clamp(t, 0.0f, 1.0f);

        glm::mat4x3 P;
        auto points = segments[currentSegment].points;
        P[0] = points[0];
        P[1] = points[1];
        P[2] = points[2];
        P[3] = points[3];
        currentPos = glm::vec4(glm::pow(t, 3), glm::pow(t, 2), t, 1) *
            glm::mat4(
                {-1, 3, -3, 1},
                {3, -6, 3, 0},
                {-3, 3, 0, 0},
                {1, 0, 0 , 0}
            ) * P;
    }


    return glm::translate(glm::mat4(1.0f), currentPos);
}
