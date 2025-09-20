#include "headers/core/Initializer.hpp"
#include "headers/graphics/Polygon.hpp"
//Include GLFW  
#include <GLFW/glfw3.h>  
//Logging
#include "spdlog/spdlog.h"

Initializer::Initializer(AppContext* appContext)
{
    this->appContext = appContext;
}

vector<std::shared_ptr<IRenderTarget>> Initializer::InitApplication()
{
    spdlog::info("Application initialization");
    InitWindow();
    spdlog::info("Initializing game objects");
    auto renderTargets = InitGameObjects();

    return renderTargets;
}

void Initializer::InitWindow()
{
    spdlog::info("Window initialization");
    glfwInit();
    // Sets up OpenGL version and core option, without backward compatibility
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "IronSource", NULL, NULL);
    if (window == NULL)
    {
        spdlog::critical("Failed to create GLFWWindow");
        glfwTerminate();
        throw 1;
    }
    glfwMakeContextCurrent(window);
    spdlog::info("Created a window");
    appContext->window = window;
}

// For now its initializing render targets, but in the future they will be replaced with game objects
vector<std::shared_ptr<IRenderTarget>> Initializer::InitGameObjects()
{
    vector<glm::vec3> vertices = vector<glm::vec3> { {0.4, 0, 0}, {0, 0.4, 0}, {0, 0.5, 0}};
    vector<glm::vec3> colors = vector<glm::vec3> { {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Polygon pol = Polygon(vertices, colors);

    return vector<std::shared_ptr<IRenderTarget>>{ std::make_shared<Polygon>(pol)};
}