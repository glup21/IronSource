#include "headers/gamelogic/Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<GameObject>> gameObjects)
    : gameObjects(gameObjects)
{
    this->camera = std::make_unique<Camera>();
}

Scene::Scene(std::vector<std::shared_ptr<GameObject>> gameObjects, std::vector<PointLight*> lights)
    : gameObjects(gameObjects)
{
    for( auto light : lights )
    {
        this->lights.push_back(std::make_unique<PointLight>(light));
    }

    this->camera = std::make_unique<Camera>();
}

std::vector<std::shared_ptr<GameObject>>* Scene::GetGameObjects()
{
    return &gameObjects;
}

std::vector<PointLight*>* Scene::GetLights()
{
    std::vector<PointLight*>* result = new std::vector<PointLight*>();

    for(auto& light : this->lights)
    {
        result->push_back(light.get());
    }

    return result;
}


Camera* Scene::GetCamera()
{
    return camera.get();
}