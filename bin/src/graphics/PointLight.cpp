#include "headers/graphics/PointLight.hpp"
#include "headers/interfaces/Observer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PointLight::PointLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q)
    : transform(transform), color(color), intensity(intensity), k_l(k_l), k_q(k_q)
{
}

glm::vec3 PointLight::GetColor()
{
    return color * intensity;
}

glm::vec3 PointLight::GetPosition()
{
    glm::mat4 matrix = transform->GetTransformMatrix();
    return glm::vec3(matrix[3]);
}

float PointLight::GetLinear() { return k_l; }
float PointLight::GetQuadratic() { return k_q; }

void PointLight::Update() { NotifyAll(); }

void PointLight::NotifyAll()
{
    for (auto* observer : observers)
        observer->Update(this);
}

void PointLight::SetPosition(glm::vec3 newPosition) {}
