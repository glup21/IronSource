#include "headers/core/Initializer.hpp"
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
    InitServices();
    spdlog::info("Initializing scene");
}

void Initializer::InitServices()
{
    this->appContext->shaderLibrary = std::make_shared<ShaderLibrary>();
}

void Initializer::InitWindow()
{
    spdlog::info("Window initialization");

    if (!glfwInit()) 
    {
        spdlog::critical("Failed to initialize GLFW");
        exit(EXIT_FAILURE);
    }

   // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24); 
    GLFWwindow* window = glfwCreateWindow(800, 600, "Iron Source", NULL, NULL);
    if (!window) 
    {
        spdlog::critical("Failed to create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) 
    {
        spdlog::critical("Failed to initialize GLEW");
        exit(EXIT_FAILURE);
    }

    spdlog::info("Created a window and initialized OpenGL");

    appContext->window = window;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 

}