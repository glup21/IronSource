#pragma once
#include "headers/gameobject/GameObject.hpp"

class Scene;
class WhacAMole : public GameObject
{
private:
    float hitTime;
    float timer;
    std::vector<glm::vec3> holes;
    float spawnInterval;
    std::shared_ptr<GameObject> mole;
    Scene* scene;
    bool moleVisible;

    void SpawnMole(glm::vec3 position);
    void RemoveMole();
public:
    WhacAMole(std::string name, std::shared_ptr<IRenderTarget> renderTarget, int id);
    ~WhacAMole() = default;

    void Update(float deltaTime) override;
    void SetScene(Scene* scene) { this->scene = scene; }
}; 