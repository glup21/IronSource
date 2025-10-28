#include "headers/graphics/SpotLight.hpp"
#include "headers/interfaces/Observer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SpotLight::SpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q, glm::vec3 direction, float cutOff, float outerCutOff)
    : transform(transform), k_l(k_l), k_q(k_q), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff)
{
    this->color = glm::normalize(color);
    this->intensity = intensity;
    this->enabled = true;
}

LightType SpotLight::GetType() const 
{
    return LightType::Spot;
}

glm::vec3 SpotLight::GetPosition()
{
    glm::mat4 matrix = transform->GetTransformMatrix();
    return glm::vec3(matrix[3]);
}

float SpotLight::GetLinear() { return k_l; }
float SpotLight::GetQuadratic() { return k_q; }

float SpotLight::GetCutOff()
{
    return cutOff;
}

float SpotLight::GetOuterCutOff()
{
    return outerCutOff;
}

glm::vec3 SpotLight::GetDirection()
{
    return direction;
}

void SpotLight::Update() { NotifyAll(); }

void SpotLight::NotifyAll()
{
    for (auto* observer : observers)
        observer->Update(this);
}

void SpotLight::SetPosition(glm::vec3 newPosition) {}
