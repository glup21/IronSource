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

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Update();
        }

        auto* lights = appContext->scene->GetLights();
        for (auto& light : *lights)
        {
            light->Update();
        }

        appContext->scene->GetCamera()->ProcessInput(appContext->window, deltaTime);

        glClearColor(0.12f, 0.09f, 0.18f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Render();
        }

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

