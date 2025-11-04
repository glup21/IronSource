#pragma once
#include <string>

class GlobalConfig
{
public:
    static std::string GetDefaultSimpleMeshVertexShaderPath() 
    {
        return "./bin/shaders/vertexShaderSimpleMesh.vert";
    }

    static std::string GetDefaultMeshVertexShaderPath() 
    {
        return "./bin/shaders/vertexShaderMesh.vert";
    }

    static std::string GetDefaultMeshFragmentShaderPath() 
    {
        return "./bin/shaders/fragmentShaderMesh.frag";
    }

    static std::string GetDefaultSimpleMeshFragmentShaderPath() 
    {
        return "./bin/shaders/fragmentShaderSimpleMesh.frag";
    }

    static std::string GetModelsPath()
    {
        return "./Models/";
    }

    static std::string GetDefaultTexturePath()
    {
        return "./Models/default_texture.png";
    }
};