#include "headers/core/Engine.hpp"
#include <GLFW/glfw3.h>  
#include "spdlog/spdlog.h"

Engine::Engine(AppContext* appContext)
{
    this->gameObjects = appContext->scene->gameObjects;
    this->appContext = appContext;
}

void Engine::Run()
{
    while (!glfwWindowShouldClose(appContext->window))
    {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

        for (auto& gameObject : gameObjects)
        {
            gameObject->Update();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& gameObject : gameObjects)
        {
            gameObject->Render();
        }

        glfwSwapBuffers(appContext->window);

        glfwPollEvents();
    }

}

