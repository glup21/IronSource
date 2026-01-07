#pragma once

#include "headers/pch.hpp"
#include <memory>

class Engine;

// Common context for passing around often used variables, like Window, Renderer and so on
struct AppContext 
{
    GLFWwindow* window;
    Engine* engine;
};

