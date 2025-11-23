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

void Transform::SetLocalPosition(glm::vec3 pos)
{
    localPosition = pos;
}

void Transform::SetLocalRotation(glm::vec3 angle)
{
    localRotation = angle;
}

void Transform::SetLocalScale(glm::vec3 s)
{
    localScale = s;
}

glm::vec3 Transform::GetLocalPosition() 
{
    return localPosition;
}

glm::vec3 Transform::GetLocalRotation()
{
    return localRotation;
}

glm::vec3 Transform::GetLocalScale() 
{
    return localScale;
}

glm::mat4 Transform::GetTransformMatrix()
{
    glm::mat4 result(1.0f);
    result = glm::translate(result, localPosition);

    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), localRotation.x, X_AXIS);
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), localRotation.y, Y_AXIS);
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), localRotation.z, Z_AXIS);
    glm::mat4 rotationMatrix = rotZ * rotY * rotX;

    result *= rotationMatrix;

    result = glm::scale(result, localScale);
    for (auto& basicTransform : basicTransforms)
    {
        result *= basicTransform->GetTransformMatrix();
    }
    return result;
}
