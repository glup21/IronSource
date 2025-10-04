#pragma once
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/gameobject/GameObject.hpp"
#include <vector>
#include <memory>

class Scene
{
public:
    std::vector<std::shared_ptr<GameObject>> gameObjects;    

    Scene(std::vector<std::shared_ptr<GameObject>> gameObjects);
    ~Scene() = default;

};