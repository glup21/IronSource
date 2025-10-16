#include "headers/services/SceneManager.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/transform/Translation.hpp"
#include "headers/transform/Rotation.hpp"
#include "headers/transform/Scale.hpp"
#include "headers/graphics/Polygon.hpp"
#include "headers/transform/DynamicRotation.hpp"
#include "headers/graphics/PointLight.hpp"

#include "./Models/sphere.h"
#include "./Models/bushes.h"
#include "./Models/gift.h"
#include "./Models/plain.h"
#include "./Models/suzi_flat.h"
#include "./Models/suzi_smooth.h"
#include "./Models/tree.h"


std::vector<Polygon*> LoadAllPredefinedModels()
{
    vector<Polygon*> polygons;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;

    // Bushes
    int vertexCount = 8730 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(bushes[i], bushes[i + 1], bushes[i + 2]);
        colors.emplace_back(bushes[i + 3], bushes[i + 4], bushes[i + 5]);
    }

    polygons.push_back(new Polygon(positions, colors));
    positions.clear();
    colors.clear();

    // Gift
    vertexCount = 66624 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(gift[i], gift[i + 1], gift[i + 2]);
        colors.emplace_back(gift[i + 3], gift[i + 4], gift[i + 5]);
    }

    polygons.push_back(new Polygon(positions, colors));
    positions.clear();
    colors.clear();

    // Plain
    vertexCount = 36;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(plain[i], plain[i + 1], plain[i + 2]);
        colors.emplace_back(plain[i + 3], plain[i + 4], plain[i + 5]);
    }

    polygons.push_back(new Polygon(positions, colors));
    positions.clear();
    colors.clear();

    // Suzi flat
    vertexCount = 2904 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(suziFlat[i], suziFlat[i + 1], suziFlat[i + 2]);
        colors.emplace_back(suziFlat[i + 3], suziFlat[i + 4], suziFlat[i + 5]);
    }

    polygons.push_back(new Polygon(positions, colors));
    positions.clear();
    colors.clear();

    // Suzi smooth
    vertexCount = 2904 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(suziSmooth[i], suziSmooth[i + 1], suziSmooth[i + 2]);
        colors.emplace_back(suziSmooth[i + 3], suziSmooth[i + 4], suziSmooth[i + 5]);
    }

    polygons.push_back(new Polygon(positions, colors));
    positions.clear();
    colors.clear();

    // Tree
    vertexCount = 92814 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(tree[i], tree[i + 1], tree[i + 2]);
        colors.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
    }

    polygons.push_back(new Polygon(positions, colors));
    positions.clear();
    colors.clear();

    return polygons;
}

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

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./shaders/firstFragmentShader.frag";

    firstPolygon->Init(shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);

    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{0.0, 0.0, 0.0}));
    firstObjectTransforms.push_back(new DynamicRotation(glm::vec3(0.0f, 0.0, 0.0), glm::radians(90.0f))); 
    firstObjectTransforms.push_back(new Scale(glm::vec3(1.0, 1.0, 1.0))); 


    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstPolygon", firstPolygon, new Transform( firstObjectTransforms ))
        }
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetSecondScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    // Replace later with initialization from text files
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;

    positions.reserve(17280 / 6);
    colors.reserve(17280 / 6);

    for (size_t i = 0; i < 17280; i += 6)
    {
        positions.emplace_back(sphere[i], sphere[i + 1], sphere[i + 2]);
        colors.emplace_back(sphere[i + 3], sphere[i + 4], sphere[i + 5]);
    }
    auto spherePolygon = new Polygon(positions, colors);


    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./shaders/firstFragmentShader.frag";

    // for(auto renderTarget : scene->renderTargets)
    // {
    //     renderTarget->Init(appContext->shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);
    // }

    // For testing multiple shader programs and transforms (replace with text reading later)
    spherePolygon->Init(shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);


    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{0.5, 0.0, 0.0}));
    firstObjectTransforms.push_back(new Scale(glm::vec3(0.25, 0.25, 0.25))); 

    std::vector<IBasicTransform*> secondObjectTransforms;
    secondObjectTransforms.push_back(new Translation(glm::vec3{0.0, 0.5, 0.0}));
    secondObjectTransforms.push_back(new Scale(glm::vec3(0.25, 0.25, 0.25))); 

    std::vector<IBasicTransform*> thirdObjectTransforms;
    thirdObjectTransforms.push_back(new Translation(glm::vec3{-0.5, 0.0, 0.0}));
    thirdObjectTransforms.push_back(new Scale(glm::vec3(0.25, 0.25, 0.25))); 

    std::vector<IBasicTransform*> forthObjectTransforms;
    forthObjectTransforms.push_back(new Translation(glm::vec3{0.0, -0.5, 0.0}));
    forthObjectTransforms.push_back(new Scale(glm::vec3(0.25, 0.25, 0.25))); 

    //    PointLight(Transform transform, glm::vec3 color, float intensity);
    PointLight* pointLight = new PointLight(Transform(), glm::vec3(1.0, 1.0, 1.0), 10.0);

    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstSphere", spherePolygon, new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", spherePolygon, new Transform( secondObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", spherePolygon, new Transform( thirdObjectTransforms )),
            std::make_shared<GameObject>("forthSphere", spherePolygon, new Transform( forthObjectTransforms )),
        },
        std::vector<PointLight*>{
            pointLight
        }
    );

    return scene;
}


std::shared_ptr<Scene> SceneManager::GetThirdScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    // Replace later with initialization from text files
    auto polygons = LoadAllPredefinedModels();

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string firstFragmentShaderPath = "./shaders/firstFragmentShader.frag";
    std::string secondFragmentShaderPath = "./shaders/secondFragmentShader.frag";

    for(auto polygon : polygons)
        polygon->Init(shaderLibrary.get(), vertexShaderPath, firstFragmentShaderPath);


    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{0.5, -0.25, 0.0}));
    firstObjectTransforms.push_back(new Scale(glm::vec3(1, 1, 1))); 
    firstObjectTransforms.push_back(new Rotation(glm::vec3(0, 15, 0))); 

    std::vector<IBasicTransform*> secondObjectTransforms;
    secondObjectTransforms.push_back(new Translation(glm::vec3{-0.4, -0.35, -0.25}));
    secondObjectTransforms.push_back(new Scale(glm::vec3(0.5, 0.5, 0.5))); 
    secondObjectTransforms.push_back(new Rotation(glm::vec3(0, 15, 0))); 

    std::vector<IBasicTransform*> thirdObjectTransforms;
    thirdObjectTransforms.push_back(new Translation(glm::vec3{0, -0.75, -0.5}));
    thirdObjectTransforms.push_back(new Scale(glm::vec3(1, 1, 1))); 
    thirdObjectTransforms.push_back(new Rotation(glm::vec3(15, 0, 0))); 

    std::vector<IBasicTransform*> forthObjectTransforms;
    forthObjectTransforms.push_back(new Translation(glm::vec3{0.3, 0.3, 0.6}));
    forthObjectTransforms.push_back(new Scale(glm::vec3(0.3, 0.3, 0.5))); 
    forthObjectTransforms.push_back(new Rotation(glm::vec3(0, 90, 0))); 

    std::vector<IBasicTransform*> fifthObjectTransforms;
    fifthObjectTransforms.push_back(new Translation(glm::vec3{-0.3, 0.3, -0.6}));
    fifthObjectTransforms.push_back(new Scale(glm::vec3(0.3, 0.3, 0.5))); 
    fifthObjectTransforms.push_back(new Rotation(glm::vec3(0, -90, 0))); 

    std::vector<IBasicTransform*> sixthObjectTransforms;
    sixthObjectTransforms.push_back(new Translation(glm::vec3{-0.75, -0.5, 0.0}));
    sixthObjectTransforms.push_back(new Scale(glm::vec3(0.25, 0.25, 0.25)));


    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstSphere", polygons[0], new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", polygons[1], new Transform( secondObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", polygons[2], new Transform( thirdObjectTransforms )),
            std::make_shared<GameObject>("forthSphere", polygons[3], new Transform( forthObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", polygons[4], new Transform( fifthObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", polygons[5], new Transform( sixthObjectTransforms ))
        }
    );

    return scene;
}
