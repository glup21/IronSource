#include "headers/gamelogic/Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
    this->gameObjects = gameObjects;
    this->camera = std::make_unique<Camera>();
}

std::vector<std::shared_ptr<GameObject>>* Scene::GetGameObjects()
{
    return &gameObjects;
}

Camera* Scene::GetCamera()
{
    return camera.get();
}