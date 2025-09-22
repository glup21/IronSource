#include "headers/core/Application.hpp"
#include "headers/core/Initializer.hpp"

#include "spdlog/spdlog.h"

void Application::Run()
{

    Initializer initializer(&appContext);
    auto renderTargets = initializer.InitApplication();
    spdlog::info("Initialization complete");

    spdlog::info("Constructing renderer");
    renderer = std::make_unique<Renderer>(renderTargets, &appContext);

    spdlog::info("Begin scene rendering");
    renderer->RenderScene();
}
