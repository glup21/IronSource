#pragma once
#include <string>
#include <vector>

class GlobalConfig
{
public:
    static std::string GetDefaultSimpleMeshVertexShaderPath();
    static std::string GetDefaultMeshVertexShaderPath();
    static std::string GetDefaultMeshFragmentShaderPath();
    static std::string GetDefaultSimpleMeshFragmentShaderPath();
    static std::string GetModelsPath();
    static std::string GetDefaultTexturePath();
    static std::vector<std::string> GetDefaultSkyboxFaces();
    static std::string GetDefaultSkyboxVertexShaderPath();
    static std::string GetDefaultSkyboxFragmentShaderPath();
};