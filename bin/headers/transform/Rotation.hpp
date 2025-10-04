#pragma once
#include "headers/transform/IBasicTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public IBasicTransform
{
private:
    glm::vec3 angles;

public:
    Rotation(glm::vec3 angles);
    void SetAngles(glm::vec3 angles);
    glm::vec3 GetAngles() const;

    glm::mat4 GetTransformMatrix() const override;
};
