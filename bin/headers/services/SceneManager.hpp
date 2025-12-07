#pragma once

#include "headers/gamelogic/Scene.hpp"
#include "headers/services/ShaderLibrary.hpp"

class SceneManager
{
private:
    SceneManager() = delete;
public:
    static std::shared_ptr<Scene> GetOnePolygonScene();
    static std::shared_ptr<Scene> GetFourSpheresScene();
    static std::shared_ptr<Scene> GetForestScene();
    static std::shared_ptr<Scene> GetSolarSystemScene();
    static std::shared_ptr<Scene> GetWhacAMoleScene();
    static std::shared_ptr<Scene> GetRacingScene();
    static std::shared_ptr<Scene> GetBezierScene();
};