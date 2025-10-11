#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/FileReaderService.hpp"
#include "spdlog/spdlog.h"

std::shared_ptr<ShaderProgram> ShaderLibrary::GetShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    spdlog::info("Trying to find shader program in shader program library");
    auto key = std::make_pair(vertexShaderPath, fragmentShaderPath);

    auto iterator = shaderPrograms.find(key);
    if (iterator != shaderPrograms.end())
    {
        spdlog::info("Found shader program in shader program library!");
        return iterator->second; 
    }

    spdlog::info("Failed to find shader program in shader library, linking new...");
    auto vertexShader = GetShader(vertexShaderPath, GL_VERTEX_SHADER);
    auto fragmentShader = GetShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    auto shaderProgram = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);
    shaderProgram->LinkShaderProgram();

    shaderPrograms[key] = shaderProgram;
    return shaderProgram;
}

std::shared_ptr<Shader> ShaderLibrary::GetShader(std::string shaderPath, GLenum shaderType)
{
    spdlog::info("Looking for shader: " + shaderPath);
    auto iterator = shaders.find(shaderPath);
    if (iterator != shaders.end())
    {
        return iterator->second; 
    }
    
    spdlog::info("Failed to find, creating new shader: " + shaderPath);
    std::string src = FileReaderService::ReadFile(shaderPath);
    auto shader = std::make_shared<Shader>(src, shaderType);
    shader->CompileShader();

    shaders[shaderPath] = shader;
    return shader;
}

void ShaderLibrary::RegisterCamera(Camera* camera)
{
    for (auto pair : this->shaderPrograms)
    {
        camera->Attach(pair.second.get());
    }
}