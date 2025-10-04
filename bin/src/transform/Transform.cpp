#include "headers/transform/Transform.hpp"

void Transform::AddBasicTransform(std::unique_ptr<IBasicTransform> basicTransform) 
{
    basicTransforms.push_back(std::move(basicTransform));
}

glm::mat4 Transform::getTransformMatrix() const
{
    glm::mat4 result(1.0f);
    for (auto& basicTransform : basicTransforms) {
        result *= basicTransform->GetTransformMatrix();
    }
    return result;
}
