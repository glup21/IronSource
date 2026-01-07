#include "headers/core/Application.hpp"
#include "headers/core/Initializer.hpp"
#include "headers/services/SceneManager.hpp"
#include "headers/services/LightFactory.hpp"

#include "spdlog/spdlog.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        AppContext* appContext = app->GetAppContext();
        Engine* engine = appContext->engine;
        switch (key)
        {
            case GLFW_KEY_1:
            {
                spdlog::info("Switching scenes: One Polygon Scene");
                std::shared_ptr<Scene> scene = SceneManager::GetOnePolygonScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            case GLFW_KEY_2:
            {
                spdlog::info("Switching scenes: Four Spheres Scene");
                std::shared_ptr<Scene> scene = SceneManager::GetFourSpheresScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            case GLFW_KEY_3:
            {
                spdlog::info("Switching scenes: Forest Scene");
                std::shared_ptr<Scene> scene = SceneManager::GetForestScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            case GLFW_KEY_4:
            {
                spdlog::info("Switching scenes: Solar System Scene");
                std::shared_ptr<Scene> scene = SceneManager::GetSolarSystemScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            case GLFW_KEY_5:
            {
                spdlog::info("Switching scenes: Whac A Mole Scene");
                std::shared_ptr<Scene> scene = SceneManager::GetWhacAMoleScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            case GLFW_KEY_6:
            {
                spdlog::info("Switching scenes: Racing Scene");
                std::shared_ptr<Scene> scene = SceneManager::GetRacingScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            case GLFW_KEY_7:
            {
                spdlog::info("Switching scenes: Bezier");
                std::shared_ptr<Scene> scene = SceneManager::GetBezierScene(engine->GetServices());
                app->SwitchScene(scene);
                engine->GetServices().shaderLibrary->RegisterCamera(scene->GetCamera());
                scene->GetCamera()->ResizeViewport(window);
                break;
            }
            default:
                break;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    AppContext* appContext = app->GetAppContext();

    appContext->engine->scene->GetCamera()->ResizeViewport(window);
}


void Application::Run()
{

    Initializer initializer(&appContext);
    initializer.InitApplication();
    spdlog::info("Initialization complete");

    spdlog::info("Constructing engine");
    engine = std::make_unique<Engine>(&appContext);
    appContext.engine = engine.get();

    glfwSetWindowUserPointer(appContext.window, this);
    glfwSetKeyCallback(appContext.window, KeyCallback);
    glfwSetFramebufferSizeCallback(appContext.window, framebuffer_size_callback);

    spdlog::info("Loading scene 4");
    engine->scene = SceneManager::GetForestScene(engine->GetServices());
    engine->shaderLibrary.RegisterCamera(engine->scene->GetCamera());

    spdlog::info("Begin scene rendering");
    engine->Run();
}

void Application::SwitchScene(std::shared_ptr<Scene> newScene)
{
    //appContext.scene->~Scene();
    engine->scene = newScene;
    engine->UpdateSceneLights();
}


AppContext* Application::GetAppContext()
{
    return &appContext;
}

Engine* Application::GetEngine()
{
    return engine.get();
}