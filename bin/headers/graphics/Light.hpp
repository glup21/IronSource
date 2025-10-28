#pragma once
#include "headers/interfaces/Subject.hpp"
#include <glm/glm.hpp>

enum class LightType {
    Ambient,
    Directional,
    Point
};

class Light : public Subject
{
protected:
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
    bool enabled = true;

public:
    Light() = default;                
    virtual ~Light() = default;       

    virtual LightType GetType() const = 0; 

    glm::vec3 GetColor() const;
    float GetIntensity() const;
    bool IsEnabled() const;

    void SetEnabled(bool value);

    virtual void Update() = 0;  
};
