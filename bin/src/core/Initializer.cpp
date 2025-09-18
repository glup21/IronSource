#include "headers/core/Initializer.hpp"

//Include GLFW  
#include <GLFW/glfw3.h>  

//Logging
#include "spdlog/spdlog.h"

void Initializer::InitApplication()
{
    glfwInit();
    // Sets up OpenGL version and core option, without backward compatibility
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "IronSource", NULL, NULL);
    if (window == NULL)
    {
        spdlog::critical("Failed to create GLFWWindow");
        glfwTerminate();
        throw 1;
    }
    glfwMakeContextCurrent(window);

}
