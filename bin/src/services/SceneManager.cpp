#include "headers/services/SceneManager.hpp"
#include "headers/transform/Transform.hpp"
#include "headers/transform/Translation.hpp"
#include "headers/transform/Rotation.hpp"
#include "headers/transform/Scale.hpp"
#include "headers/graphics/Mesh.hpp"
#include "headers/transform/DynamicRotation.hpp"
#include "headers/gameobject/Firefly.hpp"
#include "headers/services/LightFactory.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/services/MaterialFactory.hpp"
#include "headers/services/GameObjectFactory.hpp"
#include <spdlog/spdlog.h>

std::shared_ptr<Scene> SceneManager::GetFirstScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    // Replace later with initialization from text files
    auto firstMesh = std::make_shared<SimpleMesh>(
        std::vector<glm::vec3>{ 
            {0.0f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
        MaterialFactory::GetMaterial()
    );

    std::string vertexShaderPath = "./bin/shaders/vertexShader.vert";
    std::string fragmentShaderPath = "./bin/shaders/firstFragmentShader.frag";

    std::vector<IBasicTransform*> firstObjectTransforms;
    firstObjectTransforms.push_back(new Translation(glm::vec3{0.0, 0.0, 0.0}));
    firstObjectTransforms.push_back(new DynamicRotation(glm::vec3(0.0f, 0.0, 0.0), glm::radians(90.0f))); 
    firstObjectTransforms.push_back(new Scale(glm::vec3(1.0, 1.0, 1.0))); 


    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            // std::make_shared<GameObject>("firstMesh", firstMesh, new Transform( firstObjectTransforms ))
        }
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetSecondScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    // Replace later with initialization from text files

    //auto sphereMesh = MeshFactory::LoadSphere();
    auto sphereMesh = MeshFactory::LoadFromFile("./Models/formula2.obj");

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
    lights.push_back(std::unique_ptr<AmbientLight>(LightFactory::GetInstance().GetAmbientLight(glm::vec3(0.05f, 0.05f, 0.1f), 0.1f)));
    lights.push_back(std::unique_ptr<DirectionalLight>(LightFactory::GetInstance().GetDirectionalLight(
        glm::vec3(0.6f, 0.7f, 1.0f),
        glm::vec3(-0.3f, -1.0f, -0.5f), 
        0.025f 
    )));
    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{
            // std::make_shared<GameObject>("firstSphere", sphereMesh, new Transform( firstObjectTransforms )),
            // std::make_shared<GameObject>("secondSphere", sphereMesh, new Transform( secondObjectTransforms )),
            // std::make_shared<GameObject>("thirdSphere", sphereMesh, new Transform( thirdObjectTransforms )),
            // std::make_shared<GameObject>("forthSphere", sphereMesh, new Transform( forthObjectTransforms )),
        },
        std::move(lights)
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetThirdScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    std::vector<std::shared_ptr<SimpleMesh>> meshes = MeshFactory::LoadAllPredefinedModels();
    renderTargets.reserve(meshes.size() + 1);
    renderTargets.push_back(MeshFactory::LoadFromFile("./Models/formula2.obj"));
    for (auto& mesh : meshes)
    {
        renderTargets.push_back(mesh); 
    }

    std::string vertexShaderPath = "./bin/shaders/vertexShader.vert";

    std::vector<std::string> fragmentShaderPaths = {
        "./bin/shaders/fragmentShaderBlinn.frag",
        "./bin/shaders/fragmentShaderBlinn.frag",
        "./bin/shaders/fragmentShaderBlinn.frag",
        "./bin/shaders/fragmentShaderBlinn.frag"
    };

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
        new Scale(glm::vec3(0.001, 0.001, 0.001))
    };

    std::vector<std::unique_ptr<Light>> lights;
    std::vector<IBasicTransform*> lightTransforms{
        new Translation(glm::vec3{-0.75, -0.5, 0.0})
    };
    lights.push_back(std::make_unique<PointLight>(new Transform(lightTransforms), glm::vec3(1.0, 1.0, 1.0), 1.0, 2.0, 1.0));
    lightTransforms.push_back(new Translation(glm::vec3{1.0, 1.0, 0.0}));
    lights.push_back(std::make_unique<PointLight>(new Transform(lightTransforms), glm::vec3(0.0, 0.0, 1.0), 3.0, 1.0, 0.5));
    lights.push_back(std::make_unique<AmbientLight>(glm::vec3(0.05f, 0.05f, 0.1f), 0.1f));
    lights.push_back(std::make_unique<DirectionalLight>(
        glm::vec3(0.6f, 0.7f, 1.0f),
        glm::vec3(-0.3f, -1.0f, -0.5f), 
        1.0f 
    ));
    auto scene = std::make_shared<Scene>(
        std::vector<std::shared_ptr<GameObject>>{
            // std::make_shared<GameObject>("firstSphere", renderTargets[0], new Transform(firstObjectTransforms)),
            // std::make_shared<GameObject>("secondSphere", renderTargets[1], new Transform(secondObjectTransforms)),
            // std::make_shared<GameObject>("thirdSphere", renderTargets[2], new Transform(thirdObjectTransforms)),
            // std::make_shared<GameObject>("forthSphere", renderTargets[3], new Transform(forthObjectTransforms)),
            // std::make_shared<GameObject>("fifthSphere", renderTargets[4], new Transform(fifthObjectTransforms)),
            // std::make_shared<GameObject>("sixthSphere", renderTargets[5], new Transform(sixthObjectTransforms)),
            // std::make_shared<GameObject>("Car", renderTargets[6], new Transform(sixthObjectTransforms))
        },
        std::move(lights)
    );

    return scene;
}


std::shared_ptr<Scene> SceneManager::GetForthScene(std::shared_ptr<ShaderLibrary> shaderLibrary)
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    std::vector<std::shared_ptr<SimpleMesh>> meshes = MeshFactory::LoadAllPredefinedModels();
    renderTargets.reserve(meshes.size() + 1);  
    for (auto& mesh : meshes)
    {
        renderTargets.push_back(mesh); 
    }
    renderTargets.push_back(MeshFactory::LoadFromFile("./Models/shrek.obj"));

    std::vector<std::shared_ptr<GameObject>> objects;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distPos(-50.0f, 50.0f);
    std::uniform_real_distribution<float> distScale(0.5f, 1.5f);

    for (int i = 0; i < 10; i++)
    {
        auto tree = GameObjectFactory::GetInstance().GetGameObject("tree", renderTargets[5]);
        tree->transform->SetPosition(glm::vec3(distPos(gen), 0.0f, distPos(gen)));
        tree->transform->SetScale(glm::vec3(distScale(gen)));
        tree->transform->SetRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));

        objects.push_back(std::shared_ptr<GameObject>(tree));
    }

    for (int i = 0; i < 25; i++)
    {
        auto bush = GameObjectFactory::GetInstance().GetGameObject("bush", renderTargets[0]);
        bush->transform->SetPosition(glm::vec3(distPos(gen), 0.0f, distPos(gen)));
        bush->transform->SetScale(glm::vec3(distScale(gen) * 2.0f));
        bush->transform->SetRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));

        objects.push_back(std::shared_ptr<GameObject>(bush));
    }

    auto plane = GameObjectFactory::GetInstance().GetGameObject("plain", renderTargets[2]);
    plane->transform->SetPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    plane->transform->SetScale(glm::vec3(50.0f, 1.0f, 50.0f));
    objects.push_back(std::shared_ptr<GameObject>(plane));

    auto car = GameObjectFactory::GetInstance().GetGameObject("Shrek", renderTargets[6]);
    car->transform->SetPosition(glm::vec3(distPos(gen), 10.0f, distPos(gen)));
    car->transform->SetScale(glm::vec3(10.0));
    car->transform->SetRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));
    objects.push_back(std::shared_ptr<GameObject>(car));

    std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> heightDist(9.0f, 12.0f);
    std::uniform_real_distribution<float> intensityDist(0.5f, 0.75f);
    std::uniform_real_distribution<float> klDist(0.2f, 0.4f);
    std::uniform_real_distribution<float> kqDist(0.08f, 0.15f);
    std::uniform_real_distribution<float> colorShift(0.8f, 1.0f);

    for (int i = 0; i < 10; i++)
    {
        auto fireflyTransform = new Transform();
        fireflyTransform->SetPosition(glm::vec3(posDist(gen), heightDist(gen), posDist(gen)));

        glm::vec3 color = glm::vec3(1.0f, colorShift(gen), 0.3f + 0.2f * colorShift(gen));

        float intensity = intensityDist(gen);
        float k_l = klDist(gen);
        float k_q = kqDist(gen);

        auto firefly = GameObjectFactory::GetInstance().GetFireFly(
            fireflyTransform,
            10.0f,     
            color,
            intensity,
            k_l,
            k_q,
            5.0f  
        );

        objects.push_back(std::shared_ptr<Firefly>(firefly));
    }

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(std::unique_ptr<PointLight>(LightFactory::GetInstance().GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(35.0f, 15.0f, 5.0f))}), 
        glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f)));
    lights.push_back(std::unique_ptr<PointLight>(LightFactory::GetInstance().GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(-25.0f, 10.0f, -5.0f))}), 
        glm::vec3(0.0f, 1.0f, 1.0f), 2.0f, 0.09f, 0.032f)));
    lights.push_back(std::unique_ptr<PointLight>(LightFactory::GetInstance().GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(0.0f, 10.0f, 0.0f))}), 
        glm::vec3(0.0f, 0.0f, 1.0f), 3.0f, 0.09f, 0.032f)));
    lights.push_back(std::unique_ptr<AmbientLight>(LightFactory::GetInstance().GetAmbientLight(glm::vec3(0.05f, 0.05f, 0.1f), 0.1f)));
    lights.push_back(std::unique_ptr<DirectionalLight>(LightFactory::GetInstance().GetDirectionalLight(
        glm::vec3(0.6f, 0.7f, 1.0f),
        glm::vec3(-0.3f, -1.0f, -0.5f), 
        0.025f 
    )));
    // lights.push_back(std::make_unique<SpotLight>(new Transform(
    //     std::vector<IBasicTransform*>{new Translation(glm::vec3(5.0f, 10.0f, 5.0f))}),
    //     glm::vec3(1.0f, 0.0f, 0.0f),
    //     15.0f,
    //     0.09f,
    //     0.032f,
    //     glm::vec3(0.0f, -1.0f, 0.0f),
    //     30.0f,
    //     45.0f));

    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    return scene;
}

