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

void Transform::AddChild(std::unique_ptr<Transform> child)
{
    child->SetParent(this);
    children.push_back(std::move(child));
}

void Transform::SetParent(Transform* parent)
{
    this->parent = parent;
}

void Transform::SetPosition(const glm::vec3& pos)
{
    position = pos;
}

void Transform::SetRotation(const glm::quat& rot)
{
    rotation = rot;
}

void Transform::SetScale(const glm::vec3& s)
{
    scale = s;
}

glm::vec3 Transform::GetPosition() const
{
    return position;
}

glm::quat Transform::GetRotation() const
{
    return rotation;
}

glm::vec3 Transform::GetScale() const
{
    return scale;
}

glm::mat4 Transform::GetLocalMatrix()
{
    glm::mat4 result(1.0f);
    result = glm::translate(result, position);
    result *= glm::mat4_cast(rotation);
    result = glm::scale(result, scale);
    for (auto& basicTransform : basicTransforms)
    {
        result *= basicTransform->GetTransformMatrix();
    }
    return result;
}

glm::mat4 Transform::GetWorldMatrix()
{
    if (parent)
        return parent->GetWorldMatrix() * GetLocalMatrix();
    return GetLocalMatrix();
}
