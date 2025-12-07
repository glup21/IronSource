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
    static std::shared_ptr<Scene> GetOnePolygonScene();
    static std::shared_ptr<Scene> GetFourSpheresScene();
    static std::shared_ptr<Scene> GetThirdScene();
    static std::shared_ptr<Scene> GetForthScene();
    static std::shared_ptr<Scene> GetFifthScene();
    static std::shared_ptr<Scene> GetSixthScene();
    static std::shared_ptr<Scene> GetSeventhScene();
    static std::shared_ptr<Scene> GetEighthScene();
};