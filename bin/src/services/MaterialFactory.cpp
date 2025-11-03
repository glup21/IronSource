#include "headers/services/MaterialFactory.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/GlobalConfig.hpp"

std::shared_ptr<Material> MaterialFactory::GetMaterial(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    auto shaderProgram = ShaderLibrary::GetInstance().GetShaderProgram(
        vertexShaderPath,
        fragmentShaderPath);

    return std::make_shared<Material>(shaderProgram);
}
