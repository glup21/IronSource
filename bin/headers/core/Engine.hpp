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

    Engine(AppContext* appContext);
    ~Engine() = default;

    void Run();
};