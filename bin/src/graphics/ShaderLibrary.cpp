#include "headers/services/ShaderLibrary.hpp"

std::shared_ptr<ShaderProgram> ShaderLibrary::GetShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    auto key = std::make_pair(vertexShaderPath, fragmentShaderPath);

    auto iterator = shaderPrograms.find(key);
    if (iterator != shaderPrograms.end())
    {
        return iterator->second; 
    }

    auto shader = std::make_shared<ShaderProgram>();
    
    shaderPrograms[key] = shader;

    return shader;
}