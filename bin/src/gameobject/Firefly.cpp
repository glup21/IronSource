#include "headers/gameobject/Firefly.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/services/LightFactory.hpp"
#include <spdlog/spdlog.h>
#include "headers/services/GlobalConfig.hpp"

Firefly::Firefly(Transform* transform, float distance, glm::vec3 color, float intensity, float k_l, float k_q, float speed) 
    : GameObject(std::string("Firefly"), transform), distance(distance), speed(speed)
{
    // Mesh
    this->renderTarget = std::shared_ptr<SimpleMesh>(MeshFactory::LoadSphere(GlobalConfig::GetDefaultVertexShaderPath(), "./bin/shaders/fragmentShaderFirefly.frag"));
    // Light
    this->light = std::shared_ptr<PointLight>(LightFactory::GetPointLight(transform, color, intensity, k_l, k_q));

    this->transform->SetScale(glm::vec3(0.05));
}

void Firefly::Update(float deltaTime)
{
    if(!destination.has_value() || reachedDestination)
    {
        SetNewDestination();
    }

    glm::vec3 currentPos = this->transform->GetPosition();

    glm::vec3 dir = *destination - currentPos;

    float dist = glm::length(dir);

    if (dist < 0.1f)
    {
        reachedDestination = true;
        return;
    }

    dir = glm::normalize(dir);
    glm::vec3 newPos = currentPos + dir * this->speed * deltaTime;

    this->transform->SetPosition(newPos);

    this->light->Update();
}

void Firefly::SetNewDestination()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distPos(-distance, distance);
    std::uniform_real_distribution<float> heightPos(0, 10.0f);

    destination = glm::vec3(distPos(gen), heightPos(gen), distPos(gen));
    reachedDestination = false;
    
}