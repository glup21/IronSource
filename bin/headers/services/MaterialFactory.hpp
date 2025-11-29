#pragma once
#include "headers/graphics/Material.hpp"
#include "headers/services/GlobalConfig.hpp"
#include "tiny_obj_loader.h"

class MaterialFactory
{

public:
    // By default returns material for SimpleMesh
    static std::shared_ptr<Material> GetMaterial(
        std::string vertexShaderPath = GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultSimpleMeshFragmentShaderPath());

    static std::shared_ptr<Material> GetMaterialFromMtl(const tinyobj::material_t& material,
        std::string parentFolder,
        std::string vertexShaderPath = GlobalConfig::GetDefaultMeshVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultMeshFragmentShaderPath());
};