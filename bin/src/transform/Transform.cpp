#include "headers/transform/Transform.hpp"

Transform::Transform(std::vector<IBasicTransform*> basicTransforms)
{
    for (IBasicTransform* basicTransform : basicTransforms)
    {
        this->basicTransforms.push_back(std::unique_ptr<IBasicTransform>(basicTransform));
    }
}

void Transform::AddBasicTransform(std::shared_ptr<IBasicTransform> basicTransform)
{
    basicTransforms.push_back(std::move(basicTransform));
}

void Transform::SetLocalPosition(const glm::vec3& pos)
{
    localPosition = pos;
}

void Transform::SetLocalRotation(const glm::quat& rot)
{
    localRotation = rot;
}

void Transform::SetLocalScale(const glm::vec3& s)
{
    localScale = s;
}

glm::vec3 Transform::GetLocalPosition() const
{
    return localPosition;
}

glm::quat Transform::GetLocalRotation() const
{
    return localRotation;
}

glm::vec3 Transform::GetLocalScale() const
{
    return localScale;
}

glm::mat4 Transform::GetLocalMatrix()
{
    glm::mat4 result(1.0f);
    result = glm::translate(result, localPosition);
    result *= glm::mat4_cast(localRotation);
    result = glm::scale(result, localScale);
    for (auto& basicTransform : basicTransforms)
    {
        result *= basicTransform->GetTransformMatrix();
    }
    return result;
}
