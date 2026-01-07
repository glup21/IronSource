#pragma once

#include "headers/gamelogic/Scene.hpp"
#include "headers/services/ShaderLibrary.hpp"

class SceneManager
{
private:
    SceneManager() = delete;
public:
    static std::shared_ptr<Scene> GetOnePolygonScene(EngineServices services);
    static std::shared_ptr<Scene> GetFourSpheresScene(EngineServices services);
    static std::shared_ptr<Scene> GetForestScene(EngineServices services);
    static std::shared_ptr<Scene> GetSolarSystemScene(EngineServices services);
    static std::shared_ptr<Scene> GetWhacAMoleScene(EngineServices services);
    static std::shared_ptr<Scene> GetRacingScene(EngineServices services);
    static std::shared_ptr<Scene> GetBezierScene(EngineServices services);
};