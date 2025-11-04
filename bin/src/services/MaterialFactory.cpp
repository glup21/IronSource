#include "headers/services/MaterialFactory.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/GlobalConfig.hpp"
#include "headers/services/TextureFactory.hpp"

#include <filesystem>

std::shared_ptr<Material> MaterialFactory::GetMaterial(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    auto shaderProgram = ShaderLibrary::GetInstance().GetShaderProgram(
        vertexShaderPath,
        fragmentShaderPath);

    return std::make_shared<Material>(shaderProgram);
}

std::shared_ptr<Material> MaterialFactory::GetMaterialFromMtl(const tinyobj::material_t& material,
     std::string vertexShaderPath, std::string fragmentShaderPath)
{
    auto shaderProgram = ShaderLibrary::GetInstance().GetShaderProgram(
        vertexShaderPath,
        fragmentShaderPath);

    auto res = std::make_shared<Material>(
        shaderProgram,
        glm::vec3(material.ambient[0], material.ambient[1], material.ambient[2]),
        glm::vec3(material.diffuse[0], material.diffuse[1], material.diffuse[2]),
        glm::vec3(material.specular[0], material.specular[1], material.specular[2]),
        material.shininess
    );

    std::string texturePath = GlobalConfig::GetModelsPath() + material.diffuse_texname;
    if (!std::filesystem::exists(texturePath)) 
    {
        texturePath = GlobalConfig::GetDefaultTexturePath();
    }
    res->SetColorTexture(TextureFactory::GetInstance().GetTexture(texturePath));

    return res;
}