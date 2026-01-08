#pragma once
#include "headers/graphics/Material.hpp"
#include "headers/services/GlobalConfig.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/services/TextureFactory.hpp"
#include "tiny_obj_loader.h"

class MaterialFactory
{
    ShaderLibrary* shaderLibrary;
    TextureFactory* textureFactory;

public:
    MaterialFactory(ShaderLibrary* shaderLibrary, TextureFactory* textureFactory);

    // By default returns material for SimpleMesh
    std::shared_ptr<Material> GetMaterial(
        std::string vertexShaderPath = GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultSimpleMeshFragmentPhongShaderPath());

    std::shared_ptr<Material> GetMaterialFromMtl(const tinyobj::material_t& material,
        std::string parentFolder,
        std::string vertexShaderPath = GlobalConfig::GetDefaultMeshVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultMeshFragmentPhongShaderPath());
};