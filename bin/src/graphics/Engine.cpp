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
    for (auto& light : *lights)
    {
        light->Update();
    }

    while (!glfwWindowShouldClose(appContext->window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto* gameObjects = appContext->scene->GetGameObjects();

        //glClearColor(0.12f, 0.09f, 0.18f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
        appContext->scene->GetCamera()->RenderSkybox();
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS); 

        for (auto& gameObject : *gameObjects)
        {
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

