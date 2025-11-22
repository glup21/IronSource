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
    static std::shared_ptr<Scene> GetFirstScene();
    static std::shared_ptr<Scene> GetSecondScene();
    static std::shared_ptr<Scene> GetThirdScene();
    static std::shared_ptr<Scene> GetForthScene();
    static std::shared_ptr<Scene> GetFifthScene();
    static std::shared_ptr<Scene> GetSixthScene();
};