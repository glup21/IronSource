#include "headers/core/Application.hpp"
#include "headers/core/Initializer.hpp"
#include "headers/services/SceneManager.hpp"

#include "spdlog/spdlog.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        AppContext* appContext = app->GetAppContext();

        switch (key)
        {
            case GLFW_KEY_1:
            {
                spdlog::info("Switching scenes: {}", 1);
                std::shared_ptr<Scene> scene = SceneManager::GetFirstScene(app->GetAppContext()->shaderLibrary);
                app->SwitchScene(scene);
                appContext->shaderLibrary->RegisterCamera(scene->GetCamera());
                auto lights = appContext->scene->GetLights();
                for (auto light : *lights)
                {
                    appContext->shaderLibrary->RegisterLight(light);
                }

                break;
            }
            case GLFW_KEY_2:
            {
                spdlog::info("Switching scenes: {}", 2);
                std::shared_ptr<Scene> scene = SceneManager::GetSecondScene(app->GetAppContext()->shaderLibrary);
                app->SwitchScene(scene);
                appContext->shaderLibrary->RegisterCamera(scene->GetCamera());
                auto lights = appContext->scene->GetLights();
                for (auto light : *lights)
                {
                    appContext->shaderLibrary->RegisterLight(light);
                }
                break;
            }
            case GLFW_KEY_3:
            {
                spdlog::info("Switching scenes: {}", 3);
                std::shared_ptr<Scene> scene = SceneManager::GetThirdScene(app->GetAppContext()->shaderLibrary);
                app->SwitchScene(scene);
                appContext->shaderLibrary->RegisterCamera(scene->GetCamera());
                auto lights = appContext->scene->GetLights();
                for (auto light : *lights)
                {
                    appContext->shaderLibrary->RegisterLight(light);
                }
                break;
            }
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

    spdlog::info("Loading scene 3");
    appContext.scene = SceneManager::GetThirdScene(appContext.shaderLibrary);
    appContext.shaderLibrary->RegisterCamera(appContext.scene->GetCamera());

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
