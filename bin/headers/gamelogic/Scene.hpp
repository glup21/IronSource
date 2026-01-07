#pragma once
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/gameobject/GameObject.hpp"
#include "headers/gameobject/Camera.hpp"
#include "headers/graphics/Light.hpp"
#include "headers/services/GameObjectFactory.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/services/LightFactory.hpp"
#include <vector>
#include <memory>

class Scene
{
public:
    LightFactory lightFactory;
    GameObjectFactory gameObjectFactory;
    MeshFactory meshFactory;

private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::unique_ptr<Light>> lights;
    std::unique_ptr<Camera> camera;

public:
    Scene();
    ~Scene();

    void Init(std::vector<std::shared_ptr<GameObject>> gameObjects,
        std::vector<std::unique_ptr<Light>> lights = std::vector<std::unique_ptr<Light>>{});

    std::vector<std::shared_ptr<GameObject>>* GetGameObjects();
    std::vector<Light*>* GetLights();
    Camera* GetCamera();

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void DeleteGameObject(int id);
    GameObject* FindGameObjectByName(std::string name);

    void SetGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects);
    void SetLights(std::vector<std::unique_ptr<Light>> lights);
};