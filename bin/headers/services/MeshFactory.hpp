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
private:
    std::map<std::string, std::shared_ptr<Model>> models;

    MeshFactory() = default;
public:
    static MeshFactory& GetInstance()
    {
        static MeshFactory instance;
        return instance;
    }

    std::vector<std::shared_ptr<SimpleMesh>> LoadAllPredefinedModels();
    std::shared_ptr<SimpleMesh> LoadSphere(std::string vertexShaderPath = "", std::string fragmentShaderPath = "");
    std::shared_ptr<SimpleMesh> LoadTree();
    std::shared_ptr<Model> LoadFromFile(std::string fileName,
        std::string vertexShaderPath = GlobalConfig::GetDefaultMeshVertexShaderPath(),
        std::string fragmentShaderPath = GlobalConfig::GetDefaultMeshFragmentShaderPath());

    Skybox* GetSkybox();
};