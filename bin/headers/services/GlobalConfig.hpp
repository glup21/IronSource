#pragma once
#include <string>
#include <vector>

class GlobalConfig
{
public:
    // Vertex shaders
    static std::string GetDefaultSimpleMeshVertexShaderPath();
    static std::string GetDefaultMeshVertexShaderPath();
    static std::string GetDefaultSkyboxVertexShaderPath();
    // Fragment shaders
    static std::string GetDefaultSkyboxFragmentShaderPath(); 
    // Phong
    static std::string GetDefaultMeshFragmentPhongShaderPath();
    static std::string GetDefaultSimpleMeshFragmentPhongShaderPath();
    // Blinn
    static std::string GetDefaultMeshFragmentBlinnShaderPath();
    static std::string GetDefaultSimpleMeshFragmentBlinnShaderPath();

    static std::string GetModelsPath();
    static std::string GetDefaultTexturePath();
    static std::vector<std::string> GetDefaultSkyboxFaces();

    
};