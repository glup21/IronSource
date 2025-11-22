#pragma once
#include "headers/transform/IBasicTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Rotation : public IBasicTransform
{
protected:
    float angle;
    glm::vec3 axis;

public:
    Rotation(float angle, glm::vec3 axis);
    void SetAngle(float angle);
    float GetAngle();

    void SetAxis(glm::vec3 axis);
    glm::vec3 GetAxis();

    glm::mat4 GetTransformMatrix() override;
};
