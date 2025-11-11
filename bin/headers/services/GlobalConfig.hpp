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

    static std::vector<std::string> GetDefaultSkyboxFaces()
    {
        std::vector<std::string> skyboxFaces{
            "./Models/nightSky_right.png",
            "./Models/nightSky_left.png",
            "./Models/nightSky_up.png",
            "./Models/nightSky_down.png",
            "./Models/nightSky_front.png",
            "./Models/nightSky_back.png",
        };

        return skyboxFaces;
    }
    static std::string GetDefaultSkyboxVertexShaderPath()
    {
        return "./bin/shaders/vertexShaderSkybox.vert";
    }

    static std::string GetDefaultSkyboxFragmentShaderPath()
    {
        return "./bin/shaders/fragmentShaderSkybox.frag";
    }
};