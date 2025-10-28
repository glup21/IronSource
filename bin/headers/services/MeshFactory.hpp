#pragma once

#include "./Models/sphere.h"
#include "./Models/bushes.h"
#include "./Models/gift.h"
#include "./Models/plain.h"
#include "./Models/suzi_flat.h"
#include "./Models/suzi_smooth.h"
#include "./Models/tree.h"
#include "headers/graphics/Mesh.hpp"

#include <vector>

class MeshFactory
{
public:
    static std::vector<Mesh*> LoadAllPredefinedModels();
    static Mesh* LoadSphere();
    static Mesh* LoadFromFile(std::string fileName);
};