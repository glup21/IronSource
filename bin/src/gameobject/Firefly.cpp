#include "headers/gameobject/Firefly.hpp"
#include "headers/services/MeshFactory.hpp"
#include <spdlog/spdlog.h>

// REWRITE THIS MESS WITH NORMAL FACTORIES AND STOP PUSHING AROUND SHADER LIBRARY
Firefly::Firefly(Transform* transform, float distance, glm::vec3 color, float intensity, float k_l, float k_q, float speed,
    ShaderLibrary* shaderLibrary, std::string vertexShader, std::string fragmentShader) 
    : GameObject(std::string("Firefly"), transform), distance(distance), speed(speed)
{
    // Mesh
    this->renderTarget = std::shared_ptr<Mesh>(MeshFactory::LoadSphere());
    this->renderTarget->Init(shaderLibrary, vertexShader, fragmentShader);
    // Light
    this->light = std::make_shared<PointLight>(transform, color, intensity, k_l, k_q);
    shaderLibrary->RegisterLight(this->light.get());
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
    spdlog::info("Firefly moved to ({:.2f}, {:.2f}, {:.2f})", 
                 newPos.x, newPos.y, newPos.z);

    this->light->Update();
}

void Firefly::SetNewDestination()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distPos(-distance, distance);

    destination = glm::vec3(distPos(gen), 0.0f, distPos(gen));
    reachedDestination = false;
    
}