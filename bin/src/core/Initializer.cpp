#include "headers/core/Initializer.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/transform/Translation.hpp"
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
    InitServices();
    spdlog::info("Initializing scene");
    appContext->scene = InitScene();
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
}


// For now its initializing render targets, but in the future they will be replaced with game objects
std::shared_ptr<Scene> Initializer::InitScene()
{
    // Replace later with initialization from text files
    auto firstPolygon = new Polygon(
        std::vector<glm::vec3>{ 
            {0.0f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} }
    );

    auto secondPolygon = new Polygon( 
        std::vector<glm::vec3>{ 
            {1.5f, 0.5f, 0.0f},    
            {1.5f, -0.5f, 0.0f},   
            {0.5f, -0.5f, 0.0f},   
            {1.5f, 0.5f, 0.0f},    
            {0.5f, 0.5f, 0.0f},    
            {0.5f, -0.5f, 0.0f}},
        std::vector<glm::vec3>{ 
            {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f},
            {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} } 
    );

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string firstFragmentShaderPath = "./shaders/firstFragmentShader.frag";
    std::string secondFragmentShaderPath = "./shaders/secondFragmentShader.frag";

    // for(auto renderTarget : scene->renderTargets)
    // {
    //     renderTarget->Init(appContext->shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);
    // }

    // For testing multiple shader programs 
    firstPolygon->Init(appContext->shaderLibrary.get(), vertexShaderPath, firstFragmentShaderPath);
    secondPolygon->Init(appContext->shaderLibrary.get(), vertexShaderPath, secondFragmentShaderPath);

    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{-0.5, 0.3, 0.0}));

    auto scene = std::make_shared<Scene>(
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstPolygon", firstPolygon, new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondPolygon", secondPolygon, new Transform())
        }
    );

    return scene;
}