#include "headers/core/Application.hpp"
#include "headers/core/Initializer.hpp"
#include "headers/services/SceneManager.hpp"

#include "spdlog/spdlog.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

        switch (key)
        {
            case GLFW_KEY_1:
                spdlog::info("Switching scenes: {}", 1);
                app->SwitchScene(SceneManager::GetFirstScene(app->GetAppContext()->shaderLibrary));
                break;
            case GLFW_KEY_2:
                spdlog::info("Switching scenes: {}", 2);
                app->SwitchScene(SceneManager::GetSecondScene(app->GetAppContext()->shaderLibrary));
                break;
            default:
                break;
        }
    }
}

void Application::Run()
{

    Initializer initializer(&appContext);
    initializer.InitApplication();
    spdlog::info("Initialization complete");

    glfwSetWindowUserPointer(appContext.window, this);
    glfwSetKeyCallback(appContext.window, KeyCallback);

    spdlog::info("Loading scene 1");
    appContext.scene = SceneManager::GetFirstScene(appContext.shaderLibrary);

    spdlog::info("Constructing engine");
    engine = std::make_unique<Engine>(&appContext);

    spdlog::info("Begin scene rendering");
    engine->Run();
}

void Application::SwitchScene(std::shared_ptr<Scene> newScene)
{
    appContext.scene = newScene;
}

AppContext* Application::GetAppContext()
{
    return &appContext;
}
