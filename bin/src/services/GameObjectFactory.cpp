#include "headers/services/GameObjectFactory.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/gameobject/WhacAMole.hpp"
#include "spdlog/spdlog.h"
#include "headers/gamelogic/Scene.hpp"

GameObjectFactory::GameObjectFactory(Scene* scene) : scene(scene)
{

}

std::shared_ptr<GameObject> GameObjectFactory::GetGameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, Transform* transform)
{
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name, renderTarget, transform, nextId);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::GetGameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget)
{
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name, renderTarget, nextId);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::GetGameObject(std::string name, Transform* transform)
{
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name, transform, nextId);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}

std::shared_ptr<Firefly> GameObjectFactory::GetFireFly(Transform* transform, float distance, glm::vec3 color, float intensity, float k_l, float k_q, float speed)
{
    std::shared_ptr<Firefly> gameObject = std::make_shared<Firefly>(transform, distance, color, intensity, k_l, k_q, speed, nextId, scene);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::GetMole()
{
    std::shared_ptr<Model> moleMesh = scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Headcrab.obj");
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>("Mole", moleMesh, nextId);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}

std::shared_ptr<WhacAMole> GameObjectFactory::GetMachine(std::string name)
{
    auto model = scene->GetEngineServices().meshFactory->LoadFromFile("./Models/WhacAMole.obj");
    std::shared_ptr<WhacAMole> gameObject = std::make_shared<WhacAMole>(name, model, nextId, scene);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}