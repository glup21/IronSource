#pragma once

#include "headers/core/Engine.hpp"
#include "headers/core/AppContext.hpp"

class Application
{
public:
    void Run();

    Application(){};
    ~Application() = default;

    void SwitchScene(std::shared_ptr<Scene> newScene);
    AppContext* GetAppContext();
private:
    AppContext appContext;
    std::unique_ptr<Engine> engine; 

};