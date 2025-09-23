#pragma once
#include "headers/interfaces/IRenderTarget.hpp"
#include <vector>
#include <memory>

class Scene
{
public:
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;    

    Scene(std::vector<std::shared_ptr<IRenderTarget>> renderTargets);
    ~Scene() = default;

};