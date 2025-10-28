#include "headers/graphics/DirectionalLight.hpp"
#include "headers/interfaces/Observer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity)
    : direction(direction)
{
    this->color = color;
    this->intensity = intensity;
    this->enabled = true;
}

LightType DirectionalLight::GetType() const 
{
    return LightType::Directional;
}

glm::vec3 DirectionalLight::GetDirection()
{
    return direction;
}

void DirectionalLight::Update() { NotifyAll(); }

void DirectionalLight::NotifyAll()
{
    for (auto* observer : observers)
        observer->Update(this);
}

