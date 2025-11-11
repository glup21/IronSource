#include "headers/core/Engine.hpp"
#include "headers/pch.hpp"

#include "spdlog/spdlog.h"
#include <thread>
#include <chrono>

Engine::Engine(AppContext* appContext)
{
    this->appContext = appContext;
}

void Engine::Run()
{
    float targetFPS = 120.0f;
    float targetFrameTime = 1.0f / targetFPS;
    float lastFrame = 0.0f;

    auto* lights = appContext->scene->GetLights();

    while (!glfwWindowShouldClose(appContext->window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto* gameObjects = appContext->scene->GetGameObjects();

        //glClearColor(0.12f, 0.09f, 0.18f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthMask(GL_FALSE);
        appContext->scene->GetCamera()->RenderSkybox();
        glDepthMask(GL_TRUE);

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Render();
        }

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Update(deltaTime);
        }

        // Temporary to fix light counting, need to introduce a better way later
        for (auto& light : *lights)
        {
            light->Update();
        }

        appContext->shaderLibrary->UpdateLightCounts();
        appContext->scene->GetCamera()->ProcessInput(appContext->window, deltaTime);

        glfwSwapBuffers(appContext->window);
        glfwPollEvents();

        // Resets light count
        appContext->shaderLibrary->ResetShaderPrograms();

        float frameTime = glfwGetTime() - currentFrame;
        if (frameTime < targetFrameTime)
        {
            std::this_thread::sleep_for(
                std::chrono::duration<float>(targetFrameTime - frameTime)
            );
        }

    }

}

