#pragma once
#include "headers/graphics/Material.hpp"
#include "headers/services/GlobalConfig.hpp"
#include "tiny_obj_loader.h"

class MaterialFactory
{

public:
    static std::shared_ptr<Material> GetMaterial(
        std::string vertexShaderPath = GlobalConfig::GetDefaultVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultFragmentShaderPath());
    static std::shared_ptr<Material> GetMaterialFromMtl(const tinyobj::material_t& materials);
};