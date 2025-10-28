#pragma once
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/gameobject/GameObject.hpp"
#include "headers/gameobject/Camera.hpp"
#include "headers/graphics/Light.hpp"
#include <vector>
#include <memory>

class Scene
{
private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::unique_ptr<Light>> lights;
    std::unique_ptr<Camera> camera;

public:
    Scene(std::vector<std::shared_ptr<GameObject>> gameObjects);
    Scene(std::vector<std::shared_ptr<GameObject>> gameObjects, std::vector<std::unique_ptr<Light>> lights);
    ~Scene() = default;

    std::vector<std::shared_ptr<GameObject>>* GetGameObjects();
    std::vector<Light*>* GetLights();
    Camera* GetCamera();

};