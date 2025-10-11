#include "headers/core/Engine.hpp"
#include <GLFW/glfw3.h>  
#include "spdlog/spdlog.h"

Engine::Engine(AppContext* appContext)
{
    this->appContext = appContext;
}

void Engine::Run()
{
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(appContext->window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto* gameObjects = appContext->scene->GetGameObjects();
        auto* camera = appContext->scene->GetCamera();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Update();
        }

        appContext->scene->GetCamera()->ProcessInput(appContext->window, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& gameObject : *gameObjects)
        {
            gameObject->Render();
        }

        glfwSwapBuffers(appContext->window);

        glfwPollEvents();
    }

}

