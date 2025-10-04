#include "headers/core/Application.hpp"
#include "headers/core/Initializer.hpp"
#include "headers/services/SceneManager.hpp"

#include "spdlog/spdlog.h"

void Application::Run()
{

    Initializer initializer(&appContext);
    initializer.InitApplication();
    spdlog::info("Initialization complete");

    spdlog::info("Loading scene 1");
    appContext.scene = SceneManager::GetFirstScene(appContext.shaderLibrary);

    spdlog::info("Constructing engine");
    engine = std::make_unique<Engine>(&appContext);

    spdlog::info("Begin scene rendering");
    engine->Run();
}

void Application::SwitchScene(std::shared_ptr<Scene> newScene)
{
    spdlog::info("Switching scenes");
    appContext.scene = newScene;
}