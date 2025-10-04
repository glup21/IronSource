#pragma once

#include <vector>
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/gameobject/GameObject.hpp"
#include "headers/core/AppContext.hpp"
#include <memory>

using std::vector;

class Engine
{
public:
    AppContext* appContext;
    vector<std::shared_ptr<GameObject>> gameObjects;

    Engine(AppContext* appContext);
    ~Engine() = default;

    void Run();
};