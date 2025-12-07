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

    UpdateSceneLights();

    while (!glfwWindowShouldClose(appContext->window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto* gameObjects = appContext->scene->GetGameObjects();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        glDepthMask(GL_FALSE);
        appContext->scene->GetCamera()->RenderSkybox();
        glDepthMask(GL_TRUE); 

        for (auto& gameObject : *gameObjects)
        {
            if(gameObject)
                gameObject->Update(deltaTime);
        }

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Render();
        }

        appContext->scene->GetCamera()->ProcessInput(appContext->window, deltaTime);
        appContext->shaderLibrary->UpdateLightCounts();

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

void Engine::UpdateSceneLights()
{
    auto* lights = appContext->scene->GetLights();
    for (auto& light : *lights)
    {
        light->Update();
    }
}