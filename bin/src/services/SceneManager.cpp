#include "headers/services/SceneManager.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/transform/Translation.hpp"
#include "headers/transform/Rotation.hpp"
#include "headers/transform/Scale.hpp"
#include "headers/graphics/Polygon.hpp"
#include "headers/transform/DynamicRotation.hpp"

std::shared_ptr<Scene> SceneManager::GetFirstScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
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

    // For testing multiple shader programs and transforms (replace with text reading and service later)
    firstPolygon->Init(shaderLibrary.get(), vertexShaderPath, firstFragmentShaderPath);
    secondPolygon->Init(shaderLibrary.get(), vertexShaderPath, secondFragmentShaderPath);

    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{-0.5, 0.3, 0.0}));
    firstObjectTransforms.push_back(new DynamicRotation(glm::vec3(45.0f, 0.0, 1.0), glm::radians(90.0f))); 
    firstObjectTransforms.push_back(new Scale(glm::vec3(0.8, 1.2, 1.0))); 

    std::vector<IBasicTransform*> secondObjectTransforms;
    secondObjectTransforms.push_back(new Translation(glm::vec3{0.6, -0.2, 0.0}));
    secondObjectTransforms.push_back(new Rotation(glm::vec3(0.0, -30.0f, 1.0))); 
    secondObjectTransforms.push_back(new Scale(glm::vec3(0.7, 0.7, 1.0))); 


    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstPolygon", firstPolygon, new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondPolygon", secondPolygon, new Transform( secondObjectTransforms ))
        }
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetSecondScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
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

    auto thirdPolygon = new Polygon(
        std::vector<glm::vec3>{ 
            {0.0f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} }
    );

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string firstFragmentShaderPath = "./shaders/firstFragmentShader.frag";
    std::string secondFragmentShaderPath = "./shaders/secondFragmentShader.frag";

    // for(auto renderTarget : scene->renderTargets)
    // {
    //     renderTarget->Init(appContext->shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);
    // }

    // For testing multiple shader programs and transforms (replace with text reading later)
    firstPolygon->Init(shaderLibrary.get(), vertexShaderPath, firstFragmentShaderPath);
    secondPolygon->Init(shaderLibrary.get(), vertexShaderPath, secondFragmentShaderPath);
    thirdPolygon->Init(shaderLibrary.get(), vertexShaderPath, firstFragmentShaderPath);

    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{-0.5, 0.3, 0.0}));
    firstObjectTransforms.push_back(new Rotation(glm::vec3(45.0f, 0.0, 1.0))); 
    firstObjectTransforms.push_back(new Scale(glm::vec3(0.8, 1.2, 1.0))); 

    std::vector<IBasicTransform*> secondObjectTransforms;
    secondObjectTransforms.push_back(new Translation(glm::vec3{0.6, -0.2, 0.0}));
    secondObjectTransforms.push_back(new Rotation(glm::vec3(0.0, -30.0f, 1.0))); 
    secondObjectTransforms.push_back(new Scale(glm::vec3(0.7, 0.7, 1.0))); 

    std::vector<IBasicTransform*> thirdObjectTransforms;
    thirdObjectTransforms.push_back(new Translation(glm::vec3{0.2, -0.6, 0.0}));
    thirdObjectTransforms.push_back(new Rotation(glm::vec3(0.0, 35.0f, 1.0))); 
    thirdObjectTransforms.push_back(new Scale(glm::vec3(0.7, 0.24, 1.3))); 

    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstPolygon", firstPolygon, new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondPolygon", secondPolygon, new Transform( secondObjectTransforms )),
            std::make_shared<GameObject>("thirdPolygon", thirdPolygon, new Transform( thirdObjectTransforms )),
        }
    );

    return scene;
}