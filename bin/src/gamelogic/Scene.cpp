#include "headers/gamelogic/Scene.hpp"
#include "headers/services/MeshFactory.hpp"

Scene::Scene(std::vector<std::shared_ptr<GameObject>> gameObjects)
    : gameObjects(gameObjects)
{
    this->camera = std::make_unique<Camera>();
    this->camera->SetSkybox(MeshFactory::GetSkybox());
}

Scene::Scene(std::vector<std::shared_ptr<GameObject>> gameObjects,
             std::vector<std::unique_ptr<Light>> lights)
    : gameObjects(std::move(gameObjects)), lights(std::move(lights))
{
    this->camera = std::make_unique<Camera>();
    this->camera->SetSkybox(MeshFactory::GetSkybox());
}

std::vector<std::shared_ptr<GameObject>>* Scene::GetGameObjects()
{
    return &gameObjects;
}

std::vector<Light*>* Scene::GetLights()
{
    std::vector<Light*>* result = new std::vector<Light*>();

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

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
    this->gameObjects.push_back(gameObject);
}