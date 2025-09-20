#include "headers/core/Renderer.hpp"
#include <GLFW/glfw3.h>  

Renderer::Renderer(vector<std::shared_ptr<IRenderTarget>> renderTargets, AppContext* appContext)
{
    this->renderTargets = renderTargets;
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
            renderTarget->Render();

        glfwSwapBuffers(appContext->window);

        glfwPollEvents();
    }

}