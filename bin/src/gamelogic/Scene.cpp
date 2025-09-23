#include "headers/gamelogic/Scene.hpp"

Scene::Scene(std::vector<std::shared_ptr<IRenderTarget>> renderTargets)
{
    this->renderTargets = renderTargets;
}