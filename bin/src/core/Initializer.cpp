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

void Initializer::InitApplication()
{
    spdlog::info("Application initialization");
    InitWindow();
    spdlog::info("Initializing scene");
    appContext->scene = InitScene();
}

void Initializer::InitWindow()
{
    spdlog::info("Window initialization");
    glfwInit();
    // Sets up OpenGL version and core option, without backward compatibility
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "IronSource", NULL, NULL);
    if (window == NULL)
    {
        spdlog::critical("Failed to create GLFWWindow");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    spdlog::info("Created a window");
    appContext->window = window;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

}

// For now its initializing render targets, but in the future they will be replaced with game objects
std::shared_ptr<Scene> Initializer::InitScene()
{
    vector<glm::vec3> vertices = vector<glm::vec3> { {-0.6f, -0.4f, 0.f}, {0.6f, -0.4f, 0.f}, {0.f, 0.6f, 0.f}};
    vector<glm::vec3> colors = vector<glm::vec3> { {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f}};

    auto scene = std::make_shared<Scene>(vector<std::shared_ptr<IRenderTarget>>{ std::make_shared<Polygon>(vertices, colors)});

    std::string vertexShaderPath = "./shaders/vertexShader.txt";
    std::string fragmentShaderPath = "./shaders/fragmentShader.txt";

    for(auto renderTarget : scene->renderTargets)
    {
        renderTarget->Init(appContext->shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);
    }

    return scene;
}