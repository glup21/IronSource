#pragma once

#include "headers/services/MeshFactory.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/TextureFactory.hpp"

struct EngineServices
{
    MeshFactory* meshFactory;
    ShaderLibrary* shaderLibrary;
    TextureFactory* textureFactory;
    MaterialFactory* materialFactory;
};
