#include "headers/gamelogic/Scene.hpp"
Scene::~Scene()
{
    camera.reset();
    for (auto& light : lights)
    {
        if (light)
        {
            light.reset(); 
        }
    }
    lights.clear();

    gameObjects.clear();


}

Scene::Scene() : gameObjectFactory(this) 
{
    camera = std::make_unique<Camera>();
    camera->SetSkybox(MeshFactory::GetInstance().GetSkybox());
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

void Scene::DeleteGameObject(int id)
{
    for(int i = 0; i < gameObjects.size(); i++)
    {
        if(gameObjects[i]->GetId() == id && gameObjects[i]->GetIsDestructable())
        {
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}

GameObject* Scene::FindGameObjectByName(std::string name)
{
    for( auto gameObject : gameObjects )
    {
        if(gameObject->GetName() == name)
        {
            return gameObject.get();
        }
    }
    return nullptr;
}

void Scene::SetGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
    this->gameObjects = gameObjects;
}

void Scene::SetLights(std::vector<std::unique_ptr<Light>> lights)
{
    this->lights = std::move(lights);
}