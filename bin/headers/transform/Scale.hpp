#pragma once
#include "headers/transform/IBasicTransform.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public IBasicTransform
{
private:
    glm::vec3 scale;

public:
    Scale(glm::vec3 scale);
    void SetScale(glm::vec3 scale);
    glm::vec3 GetScale() const;

    glm::mat4 GetTransformMatrix() const override;
};
