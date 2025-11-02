#include "headers/gameobject/Firefly.hpp"
#include "headers/services/MeshFactory.hpp"

Firefly::Firefly(Transform* transform, int distance, glm::vec3 color, float intensity, float k_l, float k_q) : GameObject(std::string("Firefly"), transform), distance(distance)
{
    // Mesh
    this->renderTarget = std::shared_ptr<Mesh>(MeshFactory::LoadSphere());
    // Light
    this->light = std::make_shared<PointLight>(transform, color, intensity, k_l, k_q);
}

void Firefly::Update()
{

}