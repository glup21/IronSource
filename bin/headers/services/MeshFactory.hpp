#pragma once

#include "./Models/sphere.h"
#include "./Models/bushes.h"
#include "./Models/gift.h"
#include "./Models/plain.h"
#include "./Models/suzi_flat.h"
#include "./Models/suzi_smooth.h"
#include "./Models/tree.h"
#include "headers/graphics/Mesh.hpp"
#include "headers/services/GlobalConfig.hpp"
#include "headers/graphics/SimpleMesh.hpp"
#include "headers/graphics/Model.hpp"
#include "headers/graphics/Skybox.hpp"

#include <vector>
#include <string>

class MeshFactory
{
public:
    static std::vector<std::shared_ptr<SimpleMesh>> LoadAllPredefinedModels();
    static std::shared_ptr<SimpleMesh> LoadSphere(std::string vertexShaderPath = "", std::string fragmentShaderPath = "");
    static std::shared_ptr<SimpleMesh> LoadTree();
    static std::shared_ptr<Model> LoadFromFile(std::string fileName,
        std::string vertexShaderPath = GlobalConfig::GetDefaultMeshVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultMeshFragmentShaderPath());

    static Skybox* GetSkybox();
};