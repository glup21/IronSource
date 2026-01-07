#include "headers/services/GlobalConfig.hpp"

std::string GlobalConfig::GetDefaultSimpleMeshVertexShaderPath() 
{
    return "./bin/shaders/vertex/vertexShaderSimpleMesh.vert";
}

std::string GlobalConfig::GetDefaultMeshVertexShaderPath() 
{
    return "./bin/shaders/vertex/vertexShaderMesh.vert";
}

//Phong
std::string GlobalConfig::GetDefaultMeshFragmentPhongShaderPath() 
{
    return "./bin/shaders/fragment/mesh/fragmentShaderMeshPhong.frag";
}

std::string GlobalConfig::GetDefaultSimpleMeshFragmentPhongShaderPath() 
{
    return "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshPhong.frag";
}

// Blinn
std::string GlobalConfig::GetDefaultMeshFragmentBlinnShaderPath() 
{
    return "./bin/shaders/fragment/mesh/fragmentShaderMeshBlinn.frag";
}

std::string GlobalConfig::GetDefaultSimpleMeshFragmentBlinnShaderPath() 
{
    return "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshBlinn.frag";
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
    return "./bin/shaders/vertex/vertexShaderSkybox.vert";
}

std::string GlobalConfig::GetDefaultSkyboxFragmentShaderPath()
{
    return "./bin/shaders/fragment/other/fragmentShaderSkybox.frag";
}