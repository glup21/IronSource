#include "headers/gameobject/Firefly.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/services/LightFactory.hpp"
#include <spdlog/spdlog.h>
#include "headers/services/GlobalConfig.hpp"
#include "headers/gamelogic/Scene.hpp"

Firefly::Firefly(Transform* transform, float distance, glm::vec3 color, float intensity, float k_l, float k_q, float speed, int id, Scene* scene) 
    : GameObject(std::string("Firefly"), transform, id), distance(distance), speed(speed)
{
    // Mesh
    this->renderTarget = std::shared_ptr<SimpleMesh>(scene->meshFactory.LoadSphere(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragmentShaderFirefly.frag"));
    // Light
    this->light = scene->lightFactory.GetPointLight(transform, color, intensity, k_l, k_q);

    this->transform->SetLocalScale(glm::vec3(0.05));
}

void Firefly::Update(float deltaTime)
{
    this->light->Update();
    if(!destination.has_value() || reachedDestination)
    {
        SetNewDestination();
    }

    glm::vec3 currentPos = this->transform->GetLocalPosition();

    glm::vec3 dir = *destination - currentPos;

    float dist = glm::length(dir);

    if (dist < 0.1f)
    {
        reachedDestination = true;
        return;
    }

    dir = glm::normalize(dir);
    glm::vec3 newPos = currentPos + dir * this->speed * deltaTime;

    this->transform->SetLocalPosition(newPos);

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