#pragma once
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/gameobject/GameObject.hpp"
#include "headers/gameobject/Camera.hpp"
#include <vector>
#include <memory>

class Scene
{
private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::unique_ptr<Camera> camera;

public:
    Scene(std::vector<std::shared_ptr<GameObject>> gameObjects);
    ~Scene() = default;

    std::vector<std::shared_ptr<GameObject>>* GetGameObjects();
    Camera* GetCamera();

};