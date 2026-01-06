#pragma once
#include "headers/gameobject/GameObject.hpp"
#include "headers/gameobject/Firefly.hpp"

class WhacAMole;
class Scene;
class GameObjectFactory
{
    int nextId = 0;
    std::vector<std::shared_ptr<GameObject>> gameObjects = std::vector<std::shared_ptr<GameObject>>();

    Scene* scene;
public:
    GameObjectFactory(Scene* scene);

    std::shared_ptr<GameObject> GetGameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, Transform* transform);
    std::shared_ptr<GameObject> GetGameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget);
    std::shared_ptr<GameObject> GetGameObject(std::string name, Transform* transform);
    std::shared_ptr<Firefly> GetFireFly(Transform* transform, float distance, glm::vec3 color, float intensity, float k_l, float k_q, float speed);
    std::shared_ptr<GameObject> GetMole();
    std::shared_ptr<WhacAMole> GetMachine(std::string name);
};