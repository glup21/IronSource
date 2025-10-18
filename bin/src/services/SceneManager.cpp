#include "headers/services/SceneManager.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/transform/Translation.hpp"
#include "headers/transform/Rotation.hpp"
#include "headers/transform/Scale.hpp"
#include "headers/graphics/Mesh.hpp"
#include "headers/transform/DynamicRotation.hpp"

#include "./Models/sphere.h"
#include "./Models/bushes.h"
#include "./Models/gift.h"
#include "./Models/plain.h"
#include "./Models/suzi_flat.h"
#include "./Models/suzi_smooth.h"
#include "./Models/tree.h"


std::vector<Mesh*> LoadAllPredefinedModels()
{
    vector<Mesh*> meshes;
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

    meshes.push_back(new Mesh(positions, colors));
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

    meshes.push_back(new Mesh(positions, colors));
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

    meshes.push_back(new Mesh(positions, colors));
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

    meshes.push_back(new Mesh(positions, colors));
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

    meshes.push_back(new Mesh(positions, colors));
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

    meshes.push_back(new Mesh(positions, colors));
    positions.clear();
    colors.clear();

    return meshes;
}

std::shared_ptr<Scene> SceneManager::GetFirstScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    // Replace later with initialization from text files
    auto firstMesh = new Mesh(
        std::vector<glm::vec3>{ 
            {0.0f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} }
    );

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./shaders/firstFragmentShader.frag";

    firstMesh->Init(shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);

    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{0.0, 0.0, 0.0}));
    firstObjectTransforms.push_back(new DynamicRotation(glm::vec3(0.0f, 0.0, 0.0), glm::radians(90.0f))); 
    firstObjectTransforms.push_back(new Scale(glm::vec3(1.0, 1.0, 1.0))); 


    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstMesh", firstMesh, new Transform( firstObjectTransforms ))
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
    auto sphereMesh = new Mesh(positions, colors);


    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./shaders/firstFragmentShader.frag";

    // for(auto renderTarget : scene->renderTargets)
    // {
    //     renderTarget->Init(appContext->shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);
    // }

    // For testing multiple shader programs and transforms (replace with text reading later)
    sphereMesh->Init(shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);


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

    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstSphere", sphereMesh, new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", sphereMesh, new Transform( secondObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", sphereMesh, new Transform( thirdObjectTransforms )),
            std::make_shared<GameObject>("forthSphere", sphereMesh, new Transform( forthObjectTransforms )),
        }
    );

    return scene;
}


std::shared_ptr<Scene> SceneManager::GetThirdScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    // Replace later with initialization from text files
    auto meshes = LoadAllPredefinedModels();

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string firstFragmentShaderPath = "./shaders/firstFragmentShader.frag";
    std::string secondFragmentShaderPath = "./shaders/secondFragmentShader.frag";

    for(auto mesh : meshes)
        mesh->Init(shaderLibrary.get(), vertexShaderPath, firstFragmentShaderPath);


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
            std::make_shared<GameObject>("firstSphere", meshes[0], new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", meshes[1], new Transform( secondObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", meshes[2], new Transform( thirdObjectTransforms )),
            std::make_shared<GameObject>("forthSphere", meshes[3], new Transform( forthObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", meshes[4], new Transform( fifthObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", meshes[5], new Transform( sixthObjectTransforms ))
        }
    );

    return scene;
}
