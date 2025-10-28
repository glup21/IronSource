#include "headers/services/SceneManager.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/transform/Translation.hpp"
#include "headers/transform/Rotation.hpp"
#include "headers/transform/Scale.hpp"
#include "headers/graphics/Mesh.hpp"
#include "headers/transform/DynamicRotation.hpp"
#include "headers/graphics/PointLight.hpp"
#include "headers/graphics/AmbientLight.hpp"
#include "headers/graphics/Light.hpp"
#include "headers/graphics/DirectionalLight.hpp"

#include "./Models/sphere.h"
#include "./Models/bushes.h"
#include "./Models/gift.h"
#include "./Models/plain.h"
#include "./Models/suzi_flat.h"
#include "./Models/suzi_smooth.h"
#include "./Models/tree.h"

#include <spdlog/spdlog.h>


std::vector<Mesh*> LoadAllPredefinedModels()
{
    vector<Mesh*> meshes;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;

    // Bushes
    int vertexCount = 8730 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(bushes[i], bushes[i + 1], bushes[i + 2]);
        colors.emplace_back(bushes[i + 3], bushes[i + 4], bushes[i + 5]);
        normals.emplace_back(bushes[i + 3], bushes[i + 4], bushes[i + 5]);
    }

    meshes.push_back(new Mesh(positions, colors, normals));
    positions.clear();
    colors.clear();
    normals.clear();
    // Gift
    vertexCount = 66624 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(gift[i], gift[i + 1], gift[i + 2]);
        colors.emplace_back(gift[i + 3], gift[i + 4], gift[i + 5]);
        normals.emplace_back(gift[i + 3], gift[i + 4], gift[i + 5]);
    }

    meshes.push_back(new Mesh(positions, colors, normals));
    positions.clear();
    colors.clear();
    normals.clear();

    // Plain
    vertexCount = 36;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(plain[i], plain[i + 1], plain[i + 2]);
        colors.emplace_back(plain[i + 3], plain[i + 4], plain[i + 5]);
        normals.emplace_back(plain[i + 3], plain[i + 4], plain[i + 5]);
    }

    meshes.push_back(new Mesh(positions, colors, normals));
    positions.clear();
    colors.clear();
    normals.clear();

    // Suzi flat
    vertexCount = 2904 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(suziFlat[i], suziFlat[i + 1], suziFlat[i + 2]);
        colors.emplace_back(suziFlat[i + 3], suziFlat[i + 4], suziFlat[i + 5]);
        normals.emplace_back(suziFlat[i + 3], suziFlat[i + 4], suziFlat[i + 5]);
    }

    meshes.push_back(new Mesh(positions, colors, normals));
    positions.clear();
    colors.clear();
    normals.clear();

    // Suzi smooth
    vertexCount = 2904 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(suziSmooth[i], suziSmooth[i + 1], suziSmooth[i + 2]);
        colors.emplace_back(suziSmooth[i + 3], suziSmooth[i + 4], suziSmooth[i + 5]);
        normals.emplace_back(suziSmooth[i + 3], suziSmooth[i + 4], suziSmooth[i + 5]);
    }

    meshes.push_back(new Mesh(positions, colors, normals));
    positions.clear();
    colors.clear();
    normals.clear();

    // Tree
    vertexCount = 92814 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(tree[i], tree[i + 1], tree[i + 2]);
        colors.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
        normals.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
    }

    meshes.push_back(new Mesh(positions, colors, normals));
    positions.clear();
    colors.clear();
    normals.clear();

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
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
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
    auto sphereMesh = new Mesh(positions, colors, colors);


    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./shaders/fragmentShaderBlinn.frag";

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

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(std::make_unique<PointLight>(new Transform(), glm::vec3(1.0, 1.0, 1.0), 1.0, 2.0, 1.0));

    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstSphere", sphereMesh, new Transform( firstObjectTransforms )),
            std::make_shared<GameObject>("secondSphere", sphereMesh, new Transform( secondObjectTransforms )),
            std::make_shared<GameObject>("thirdSphere", sphereMesh, new Transform( thirdObjectTransforms )),
            std::make_shared<GameObject>("forthSphere", sphereMesh, new Transform( forthObjectTransforms )),
        },
        std::move(lights)
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetThirdScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    auto meshes = LoadAllPredefinedModels();

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    // std::vector<std::string> fragmentShaderPaths = {
    //     "./shaders/fragmentShaderConstant.frag",
    //     "./shaders/fragmentShaderLambert.frag",
    //     "./shaders/fragmentShaderPhong.frag",
    //     "./shaders/fragmentShaderBlinn.frag"
    // };

    std::vector<std::string> fragmentShaderPaths = {
        "./shaders/fragmentShaderBlinn.frag",
        "./shaders/fragmentShaderBlinn.frag",
        "./shaders/fragmentShaderBlinn.frag",
        "./shaders/fragmentShaderBlinn.frag"
    };

    for (size_t i = 0; i < meshes.size(); ++i)
    {
        std::string fragPath = fragmentShaderPaths[i % fragmentShaderPaths.size()];
        meshes[i]->Init(shaderLibrary.get(), vertexShaderPath, fragPath);
        spdlog::info("Initialized mesh {} with shader: {}", i, fragPath);
    }

    std::vector<IBasicTransform*> firstObjectTransforms{
        new Translation(glm::vec3{0.5, -0.25, 0.0}),
        new Scale(glm::vec3(1, 1, 1)),
        new Rotation(glm::vec3(0, 15, 0))
    };

    std::vector<IBasicTransform*> secondObjectTransforms{
        new Translation(glm::vec3{-0.4, -0.35, -0.25}),
        new Scale(glm::vec3(0.5, 0.5, 0.5)),
        new Rotation(glm::vec3(0, 15, 0))
    };

    std::vector<IBasicTransform*> thirdObjectTransforms{
        new Translation(glm::vec3{0, -0.75, -0.5}),
        new Scale(glm::vec3(1, 1, 1)),
        new Rotation(glm::vec3(15, 0, 0))
    };

    std::vector<IBasicTransform*> forthObjectTransforms{
        new Translation(glm::vec3{0.3, 0.3, 0.6}),
        new Scale(glm::vec3(0.3, 0.3, 0.5)),
        new Rotation(glm::vec3(0, 90, 0))
    };

    std::vector<IBasicTransform*> fifthObjectTransforms{
        new Translation(glm::vec3{-0.3, 0.3, -0.6}),
        new Scale(glm::vec3(0.3, 0.3, 0.5)),
        new Rotation(glm::vec3(0, -90, 0))
    };

    std::vector<IBasicTransform*> sixthObjectTransforms{
        new Translation(glm::vec3{-0.75, -0.5, 0.0}),
        new Scale(glm::vec3(0.25, 0.25, 0.25))
    };

    std::vector<std::unique_ptr<Light>> lights;
    std::vector<IBasicTransform*> lightTransforms{
        new Translation(glm::vec3{-0.75, -0.5, 0.0})
    };
    lights.push_back(std::make_unique<PointLight>(new Transform(lightTransforms), glm::vec3(1.0, 1.0, 1.0), 1.0, 2.0, 1.0));
    lightTransforms.push_back(new Translation(glm::vec3{1.0, 1.0, 0.0}));
    lights.push_back(std::make_unique<PointLight>(new Transform(lightTransforms), glm::vec3(0.0, 0.0, 1.0), 3.0, 1.0, 0.5));

    auto scene = std::make_shared<Scene>(
        std::vector<std::shared_ptr<GameObject>>{
            std::make_shared<GameObject>("firstSphere", meshes[0], new Transform(firstObjectTransforms)),
            std::make_shared<GameObject>("secondSphere", meshes[1], new Transform(secondObjectTransforms)),
            std::make_shared<GameObject>("thirdSphere", meshes[2], new Transform(thirdObjectTransforms)),
            std::make_shared<GameObject>("forthSphere", meshes[3], new Transform(forthObjectTransforms)),
            std::make_shared<GameObject>("fifthSphere", meshes[4], new Transform(fifthObjectTransforms)),
            std::make_shared<GameObject>("sixthSphere", meshes[5], new Transform(sixthObjectTransforms))
        },
        std::move(lights)
    );

    return scene;
}


std::shared_ptr<Scene> SceneManager::GetForthScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    auto meshes = LoadAllPredefinedModels();

    std::string vertexShaderPath = "./shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./shaders/fragmentShaderBlinn.frag";

    for (auto& mesh : meshes)
        mesh->Init(shaderLibrary.get(), vertexShaderPath, fragmentShaderPath);

    std::vector<std::shared_ptr<GameObject>> objects;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distPos(-50.0f, 50.0f);
    std::uniform_real_distribution<float> distScale(0.5f, 1.5f);

    for (int i = 0; i < 400; ++i)
    {
        std::vector<IBasicTransform*> treeTransforms{
            new Translation(glm::vec3(distPos(gen), 0.0f, distPos(gen))),
            new Scale(glm::vec3(distScale(gen))),
            new Rotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f))
        };
        objects.push_back(std::make_shared<GameObject>("tree", meshes[5], new Transform(treeTransforms)));
    }

    for (int i = 0; i < 1600; ++i)
    {
        std::vector<IBasicTransform*> bushTransforms{
            new Translation(glm::vec3(distPos(gen), 0.0f, distPos(gen))),
            new Scale(glm::vec3(distScale(gen) * 2.0f)),
            new Rotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f))
        };
        objects.push_back(std::make_shared<GameObject>("bush", meshes[0], new Transform(bushTransforms)));
    }

    std::vector<IBasicTransform*> plainTransforms{
        new Translation(glm::vec3(0.0f, -0.01f, 0.0f)),
        new Scale(glm::vec3(50.0f, 1.0f, 50.0f))
    };
    objects.push_back(std::make_shared<GameObject>("plain", meshes[2], new Transform(plainTransforms)));

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(std::make_unique<PointLight>(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(35.0f, 15.0f, 5.0f))}), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f));
    lights.push_back(std::make_unique<PointLight>(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(-25.0f, 10.0f, -5.0f))}), glm::vec3(0.0f, 1.0f, 1.0f), 2.0f, 0.09f, 0.032f));
    //lights.push_back(std::make_unique<PointLight>(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(0.0f, 10.0f, 0.0f))}), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 0.09f, 0.032f));
    lights.push_back(std::make_unique<AmbientLight>(glm::vec3(0.05f, 0.05f, 0.1f), 0.01f));
    lights.push_back(std::make_unique<DirectionalLight>(
        glm::vec3(0.6f, 0.7f, 1.0f),
        glm::vec3(-0.3f, -1.0f, -0.5f), 
        0.050f 
    ));


    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    return scene;
}

