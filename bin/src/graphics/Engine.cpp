#include "headers/core/Engine.hpp"
#include <GLFW/glfw3.h>  
#include "spdlog/spdlog.h"
#include <thread>
#include <chrono>

Engine::Engine(AppContext* appContext)
{
    this->appContext = appContext;
}

void Engine::Run()
{
    float targetFPS = 60.0f;
    float targetFrameTime = 1.0f / targetFPS;

    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(appContext->window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto* gameObjects = appContext->scene->GetGameObjects();
        auto* lights = appContext->scene->GetLights();
        auto* camera = appContext->scene->GetCamera();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Update();
        }

        for (auto& light : *lights)
        {
            light->Update();
        }

        appContext->scene->GetCamera()->ProcessInput(appContext->window, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Render();
        }

        glfwSwapBuffers(appContext->window);

        glfwPollEvents();

        float frameTime = glfwGetTime() - currentFrame;
        if (frameTime < targetFrameTime)
        {
            std::this_thread::sleep_for(
                std::chrono::duration<float>(targetFrameTime - frameTime)
            );
        }
    }

}

