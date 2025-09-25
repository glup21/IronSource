#include "headers/core/Renderer.hpp"
#include <GLFW/glfw3.h>  
#include "spdlog/spdlog.h"

Renderer::Renderer(AppContext* appContext)
{
    this->renderTargets = appContext->scene->renderTargets;
    this->appContext = appContext;
}

void Renderer::RenderScene()
{
    // How do we stop rendering in this configuration?
    // Maybe some static function in WindowManager or something?
    while (!glfwWindowShouldClose(appContext->window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

        for (auto& renderTarget : renderTargets)
        {
            renderTarget->Render();
        }

        glfwSwapBuffers(appContext->window);

        glfwPollEvents();
    }

}

