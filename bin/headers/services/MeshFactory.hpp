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

#include <vector>
#include <string>

class MeshFactory
{
public:
    static std::vector<Mesh*> LoadAllPredefinedModels();
    static Mesh* LoadSphere(std::string vertexShaderPath = "", std::string fragmentShaderPath = "");
    static Mesh* LoadFromFile(std::string fileName);
};