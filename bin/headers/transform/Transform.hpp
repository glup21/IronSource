#pragma once

#include "headers/transform/IBasicTransform.hpp"

#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Transform
{
private:
    glm::vec3 localPosition{0.0f};
    glm::vec3 localRotation{0.0f}; // Euler angles: pitch, yaw, roll
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

    void SetLocalPosition(glm::vec3 pos);
    void SetLocalRotation(glm::vec3 angle);
    void SetLocalScale(glm::vec3 s);

    glm::vec3 GetLocalPosition();
    glm::vec3 GetLocalRotation();
    glm::vec3 GetLocalScale();
};
