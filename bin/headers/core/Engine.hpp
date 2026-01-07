#pragma once

#include <vector>
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/gameobject/GameObject.hpp"
#include "headers/core/AppContext.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/TextureFactory.hpp"
#include "headers/core/EngineServices.hpp"
#include "headers/services/MaterialFactory.hpp"
#include "headers/core/AppContext.hpp"
#include <memory>

using std::vector;
class Engine
{
public:
    AppContext* appContext;
    ShaderLibrary shaderLibrary;
    TextureFactory textureFactory;
    MaterialFactory materialFactory;
    MeshFactory meshFactory;

    std::shared_ptr<Scene> scene;

    Engine(AppContext* appContext);
    ~Engine() = default;

    void Run();

    void UpdateSceneLights();
    EngineServices GetServices();
};
