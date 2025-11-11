#include "headers/services/GameObjectFactory.hpp"

/*
    GameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, Transform* transform, int id);
    GameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, int id);
    GameObject(std::string name, Transform* transform, int id);
*/

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
    std::shared_ptr<Firefly> gameObject = std::make_shared<Firefly>(transform, distance, color, intensity, k_l, k_q, speed, nextId);
    nextId++;

    gameObjects.push_back(gameObject);
    return gameObject;
}