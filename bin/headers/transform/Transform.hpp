#pragma once

#include "headers/transform/IBasicTransform.hpp"

#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Transform
{
private:
    glm::vec3 localPosition{0.0f};
    glm::quat localRotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 localScale{1.0f};

    Transform* parent = nullptr;
    std::vector<Transform*> children;
    std::vector<std::shared_ptr<IBasicTransform>> basicTransforms;

public:
    Transform() = default;
    Transform(std::vector<IBasicTransform*> basicTransforms);
    ~Transform() = default;

    glm::mat4 GetLocalMatrix();

    void AddBasicTransform(std::shared_ptr<IBasicTransform> basicTransform);

    void SetLocalPosition(const glm::vec3& pos);
    void SetLocalRotation(const glm::quat& rot);
    void SetLocalScale(const glm::vec3& s);
    glm::vec3 GetLocalPosition() const;
    glm::quat GetLocalRotation() const;
    glm::vec3 GetLocalScale() const;
};
