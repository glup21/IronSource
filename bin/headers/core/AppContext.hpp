#pragma once

#include "headers/pch.hpp"

#include "headers/gamelogic/Scene.hpp"
#include <memory>
#include "headers/services/ShaderLibrary.hpp"

// Common context for passing around often used variables, like Window, Renderer and so on
struct AppContext 
{
    GLFWwindow* window;
    std::shared_ptr<Scene> scene;
    ShaderLibrary* shaderLibrary;
};

