#include "headers/graphics/PointLight.hpp"
#include "headers/interfaces/Observer.hpp"

PointLight::PointLight(Transform transform, glm::vec3 color, float intensity)
    : transform(std::make_unique<Transform>(transform)), color(color), intensity(intensity)
{

}

void PointLight::NotifyAll() 
{
    for(auto* observer : observers)
    {
        observer->Update(this);
    }
}
