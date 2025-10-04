#include "headers/transform/Transform.hpp"

Transform::Transform(std::vector<IBasicTransform*> basicTransforms)
{
    for (IBasicTransform* basicTransform : basicTransforms)
    {
        this->basicTransforms.push_back(std::unique_ptr<IBasicTransform>(basicTransform));
    }
}

void Transform::AddBasicTransform(std::unique_ptr<IBasicTransform> basicTransform) 
{
    basicTransforms.push_back(std::move(basicTransform));
}

glm::mat4 Transform::GetTransformMatrix() const
{
    glm::mat4 result(1.0f);
    for (auto& basicTransform : basicTransforms) {
        result *= basicTransform->GetTransformMatrix();
    }
    return result;
}
