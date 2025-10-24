#include "headers/graphics/PointLight.hpp"
#include "headers/interfaces/Observer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PointLight::PointLight(Transform* transform, glm::vec3 color, float intensity)
    : transform(transform), color(color), intensity(intensity)
{
}

glm::vec3 PointLight::GetColor()
{
    return this->color * this->intensity;
}

glm::vec3 PointLight::GetPosition()
{
    glm::mat4 matrix = this->transform->GetTransformMatrix();

    return glm::vec3(matrix[3]);
}

void PointLight::Update()
{
    NotifyAll();
}

void PointLight::NotifyAll() 
{
    for (auto* observer : observers)
    {
        observer->Update(this);
    }
}

void PointLight::SetPosition(glm::vec3 newPosition)
{
    
}