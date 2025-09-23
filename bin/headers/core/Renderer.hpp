#pragma once

#include <vector>
#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/core/AppContext.hpp"
#include <memory>

using std::vector;

class Renderer
{
public:
    AppContext* appContext;
    vector<std::shared_ptr<IRenderTarget>> renderTargets;

    Renderer(AppContext* appContext);
    ~Renderer() = default;

    void RenderScene();
};