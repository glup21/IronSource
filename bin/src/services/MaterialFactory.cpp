#include "headers/services/MaterialFactory.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/GlobalConfig.hpp"
#include "headers/services/TextureFactory.hpp"

#include <filesystem>

MaterialFactory::MaterialFactory(ShaderLibrary* shaderLibrary, TextureFactory* textureFactory) :
    shaderLibrary(shaderLibrary), textureFactory(textureFactory)
{

}

std::shared_ptr<Material> MaterialFactory::GetMaterial(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    auto shaderProgram = shaderLibrary->GetShaderProgram(
        vertexShaderPath,
        fragmentShaderPath);

    return std::make_shared<Material>(shaderProgram);
}

std::shared_ptr<Material> MaterialFactory::GetMaterialFromMtl(const tinyobj::material_t& material,
    std::string parentFolder,
    std::string vertexShaderPath,
    std::string fragmentShaderPath)
{
    auto shaderProgram = shaderLibrary->GetShaderProgram(
        vertexShaderPath,
        fragmentShaderPath);

    auto res = std::make_shared<Material>(
        shaderProgram,
        glm::vec3(material.ambient[0], material.ambient[1], material.ambient[2]),
        glm::vec3(material.diffuse[0], material.diffuse[1], material.diffuse[2]),
        glm::vec3(material.specular[0], material.specular[1], material.specular[2]),
        material.shininess/10
    );

    std::string colorTexturePath = parentFolder + "/" + material.diffuse_texname;
    if (!std::filesystem::exists(colorTexturePath) || std::filesystem::is_directory(colorTexturePath)) 
    {
        colorTexturePath = GlobalConfig::GetDefaultTexturePath();
    }
    res->AddColorTexture(textureFactory->GetTexture(colorTexturePath));

    std::string normalTexturePath = parentFolder + material.normal_texname;
    if (std::filesystem::exists(normalTexturePath)) 
    {
        res->SetNormalTexture(textureFactory->GetTexture(normalTexturePath));
    }
    

    return res;
}