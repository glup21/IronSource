#include "headers/core/Application.hpp"
#include "headers/core/Initializer.hpp"

#include "spdlog/spdlog.h"

void Application::Run()
{

    Initializer initializer(&appContext);
    initializer.InitApplication();
    spdlog::info("Initialization complete");

    spdlog::info("Constructing engine");
    engine = std::make_unique<Engine>(&appContext);

    spdlog::info("Begin scene rendering");
    engine->Run();
}
