#pragma once
#include "headers/transform/IBasicTransform.hpp"

class Translation : public IBasicTransform
{
private:
    glm::vec3 position;

public:
    Translation(glm::vec3 pos);
    void SetPosition(glm::vec3 pos);
    glm::vec3 GetPosition() const;

    glm::mat4 GetTransformMatrix() override;
};
