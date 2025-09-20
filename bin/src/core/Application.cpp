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

	int width, height;
	glfwGetFramebufferSize(appContext.window, &width, &height);
	float ratio = width / (float)height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    renderer->RenderScene();
}
