#include "headers/core/Initializer.hpp"
#include "headers/pch.hpp"

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
    this->appContext->shaderLibrary = &ShaderLibrary::GetInstance();
}

void Initializer::InitWindow()
{
    spdlog::info("Window initialization");

    if (!glfwInit()) 
    {
        spdlog::critical("Failed to initialize GLFW");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_SAMPLES, 8);
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

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}