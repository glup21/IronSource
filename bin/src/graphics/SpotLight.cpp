#include "headers/graphics/SpotLight.hpp"
#include "headers/interfaces/Observer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SpotLight::SpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q, glm::vec3 direction,
     float cutOff, float outerCutOff, std::shared_ptr<Texture> lightTexture)
    : transform(transform), k_l(k_l), k_q(k_q), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), lightTexture(lightTexture)
{
    this->color = glm::normalize(color);
    this->intensity = intensity;
    this->enabled = true;
}

LightType SpotLight::GetType() const 
{
    return LightType::Spot;
}

float SpotLight::GetLinear() { return k_l; }
float SpotLight::GetQuadratic() { return k_q; }

float SpotLight::GetCutOff()
{
    return cutOff;
}

Texture* SpotLight::GetLightTexture()
{
    return lightTexture.get();
}


float SpotLight::GetOuterCutOff()
{
    return outerCutOff;
}

glm::vec3 SpotLight::GetDirection()
{
    return direction;
}

void SpotLight::Update() 
{
    NotifyAll();
}

void SpotLight::NotifyAll()
{
    for (auto* observer : observers)
        observer->Update(this);
}

void SpotLight::SetDirection(glm::vec3 newDirection)
{
    this->direction = newDirection;
}

