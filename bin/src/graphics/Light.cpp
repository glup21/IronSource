#include "headers/graphics/Light.hpp"


glm::vec3 Light::GetColor() const 
{
    return color; 
}

float Light::GetIntensity() const 
{ 
    return intensity; 
}

bool Light::IsEnabled() const 
{
    return enabled; 
}

void Light::SetEnabled(bool value) 
{ 
    enabled = value; 
    NotifyAll(); 
}