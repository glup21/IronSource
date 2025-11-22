#pragma once
#include "headers/transform/IBasicTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

static const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
static const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);

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
