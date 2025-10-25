#pragma once

#include "headers/gamelogic/Scene.hpp"
#include "headers/services/ShaderLibrary.hpp"

class SceneManager
{
private:
    SceneManager() = delete;
public:
    // This is the worst code Ive written in a year
    // TO DO: Replace later with proper JSON scene import
    static std::shared_ptr<Scene> GetFirstScene(std::shared_ptr<ShaderLibrary> shaderLibrary);
    static std::shared_ptr<Scene> GetSecondScene(std::shared_ptr<ShaderLibrary> shaderLibrary);
    static std::shared_ptr<Scene> GetThirdScene(std::shared_ptr<ShaderLibrary> shaderLibrary);
    static std::shared_ptr<Scene> GetForthScene(std::shared_ptr<ShaderLibrary> shaderLibrary);
};