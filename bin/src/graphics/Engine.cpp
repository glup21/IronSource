#include "headers/core/Engine.hpp"
#include "headers/pch.hpp"
#include "headers/gamelogic/Scene.hpp"
#include "spdlog/spdlog.h"
#include <thread>
#include <chrono>

/*
    MeshFactory meshFactory;
    ShaderLibrary shaderLibrary;
    TextureFactory textureFactory;
    MaterialFactory* materialFactory;
*/

Engine::Engine(AppContext* appContext) :
    shaderLibrary(), textureFactory(), materialFactory(&shaderLibrary, &textureFactory),  meshFactory(&materialFactory, &shaderLibrary)
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

        auto* gameObjects = scene->GetGameObjects();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        glDepthMask(GL_FALSE);
        scene->GetCamera()->RenderSkybox();
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

        scene->GetCamera()->ProcessInput(appContext->window, deltaTime);
        shaderLibrary.UpdateLightCounts(
            scene->GetSceneServices().lightFactory->ambientLightCount,
            scene->GetSceneServices().lightFactory->pointLightCount,
            scene->GetSceneServices().lightFactory->directionalLightCount,
            scene->GetSceneServices().lightFactory->spotLightCount        
        );

        glfwSwapBuffers(appContext->window);
        glfwPollEvents();

        // Resets light count
        shaderLibrary.ResetShaderPrograms();

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
    auto* lights = scene->GetLights();
    for (auto& light : *lights)
    {
        light->Update();
    }
}

EngineServices Engine::GetServices()
{
    return { &meshFactory, &shaderLibrary, &textureFactory, &materialFactory };
}