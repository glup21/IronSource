#pragma once
#include "headers/graphics/Light.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/graphics/Texture.hpp"
class SpotLight : public Light
{
private:
    
    float k_l;
    float k_q;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    std::shared_ptr<Texture> lightTexture;

    void NotifyAll() override;

public:
    Transform* transform;
    // Replace manual direction with proper Transform 
    SpotLight(Transform* transform, glm::vec3 color, float intensity, float k_l, float k_q, glm::vec3 direction,
         float cutOff, float outerCutOff, std::shared_ptr<Texture> lightTexture = nullptr);
    ~SpotLight() = default;

    LightType GetType() const override;
    glm::vec3 GetPosition();
    float GetLinear();
    float GetQuadratic();
    float GetCutOff();
    float GetOuterCutOff();
    glm::vec3 GetDirection();

    Texture* GetLightTexture();

    void SetDirection(glm::vec3 newDirection);
    void Update();
};
