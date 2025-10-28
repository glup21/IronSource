#include "headers/graphics/AmbientLight.hpp"
#include "headers/interfaces/Observer.hpp"

AmbientLight::AmbientLight(glm::vec3 color, float intensity)
{
    this->color = glm::normalize(color);
    this->intensity = intensity;
    this->enabled = true;
}

void AmbientLight::NotifyAll()
{
    for (auto observer : observers)
    {
        observer->Update(this);
    }
        
}

LightType AmbientLight::GetType() const
{
    return LightType::Ambient;
}


void AmbientLight::Update()
{
    NotifyAll();
}
