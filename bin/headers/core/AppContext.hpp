#pragma once

#include <GLFW/glfw3.h>  
#include "headers/gamelogic/Scene.hpp"
#include <memory>

// Common context for passing around often used variables, like Window, Renderer and so on
struct AppContext 
{
    GLFWwindow* window;
    std::shared_ptr<Scene> scene;
};

