#pragma once
#include "headers/transform/IBasicTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>

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

    void AddRotation(float angle, glm::vec3 axis);

    glm::mat4 GetTransformMatrix() override;
};
