#pragma once

#include "headers/core/Renderer.hpp"
#include "headers/core/AppContext.hpp"

class Application
{
public:
    void Run();

    Application(){};
    ~Application() = default;

private:
    AppContext appContext;
    std::unique_ptr<Renderer> renderer; 
};