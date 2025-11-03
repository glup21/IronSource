#pragma once
#include "headers/graphics/Material.hpp"
#include "headers/services/GlobalConfig.hpp"

class MaterialFactory
{

public:
    static std::shared_ptr<Material> GetMaterial(
        std::string vertexShaderPath = GlobalConfig::GetDefaultVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultFragmentShaderPath());
};