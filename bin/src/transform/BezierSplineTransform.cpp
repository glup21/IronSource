#include "headers/transform/BezierSplineTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>

BezierSplineTransform::BezierSplineTransform(std::vector<glm::vec3> points, float speed) 
    : speed(speed)
{
    lastTime = glfwGetTime();
    t = 0.0f;

    for(int i = 0; i + 4 < points.size(); i += 3)
    {
        std::vector<glm::vec3> segmentPoints = {
            points[i + 0], 
            points[i + 2], 
            points[i + 4],
            points[i + 3]  
        };

        segments.push_back({segmentPoints});
    }
}

glm::vec3 GetBezierTangentVector(std::vector<glm::vec3> points, float t)
{
    return 3.0f * ( (float)glm::pow((1 - t), 2) * (points[1] - points[0]) + 2 * (1 - t)*t*(points[2] - points[1])
        + t*t*(points[3]-points[2]));
}

glm::mat4 BezierSplineTransform::GetTransformMatrix()
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (segments.empty())
    {
        return glm::mat4(1.0f);  
    }

    auto points = segments[currentSegment].points;
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
        currentPos = (float)glm::pow((1 - t), 3) * points[0] +
            3*(float)glm::pow((1 - t), 2) * t * points[1] +
            3*(1 - t) * (t*t) * points[2] + 
            t*t*t * points[3];
    }

    glm::vec3 tangent = glm::normalize(GetBezierTangentVector(points, t)); 
    glm::vec3 up = glm::vec3(0, 1, 0); 

    glm::vec3 right = glm::normalize(glm::cross(up, tangent)); 
    up = glm::cross(tangent, right);

    glm::mat4 rotation(1.0f);
    rotation[0] = glm::vec4(right, 0.0f);  
    rotation[1] = glm::vec4(up, 0.0f);      
    rotation[2] = glm::vec4(tangent, 0.0f); 
    rotation[3] = glm::vec4(0, 0, 0, 1);   

    return glm::translate(glm::mat4(1.0f), currentPos) * rotation;
}
