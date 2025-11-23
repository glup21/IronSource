#include "headers/services/GlobalConfig.hpp"

std::string GlobalConfig::GetDefaultSimpleMeshVertexShaderPath() 
{
    return "./bin/shaders/vertexShaderSimpleMesh.vert";
}

std::string GlobalConfig::GetDefaultMeshVertexShaderPath() 
{
    return "./bin/shaders/vertexShaderMesh.vert";
}

std::string GlobalConfig::GetDefaultMeshFragmentShaderPath() 
{
    return "./bin/shaders/fragmentShaderMesh.frag";
}

std::string GlobalConfig::GetDefaultSimpleMeshFragmentShaderPath() 
{
    return "./bin/shaders/fragmentShaderSimpleMesh.frag";
}

std::string GlobalConfig::GetModelsPath()
{
    return "./Models/";
}

std::string GlobalConfig::GetDefaultTexturePath()
{
    return "./Models/default_texture.png";
}

std::vector<std::string> GlobalConfig::GetDefaultSkyboxFaces()
{
    std::vector<std::string> skyboxFaces{
        "./Models/px.png",
        "./Models/ny.png",
        "./Models/py.png",
        "./Models/ny.png",
        "./Models/nz.png",
        "./Models/pz.png",
    };

    return skyboxFaces;
}
std::string GlobalConfig::GetDefaultSkyboxVertexShaderPath()
{
    return "./bin/shaders/vertexShaderSkybox.vert";
}

std::string GlobalConfig::GetDefaultSkyboxFragmentShaderPath()
{
    return "./bin/shaders/fragmentShaderSkybox.frag";
}