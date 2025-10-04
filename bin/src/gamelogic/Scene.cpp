#include "headers/gamelogic/Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
    this->gameObjects = gameObjects;
}