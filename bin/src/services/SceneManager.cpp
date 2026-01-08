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
#include "headers/services/TextureFactory.hpp"
#include "headers/transform/DynamicTranslation.hpp"
#include "headers/gameobject/WhacAMole.hpp"
#include "headers/transform/CurvedTranslation.hpp"
#include "headers/transform/DynamicPolylineTranslation.hpp"
#include "headers/transform/DummyTransform.hpp"
#include "headers/transform/BezierSplineTransform.hpp"
#include <spdlog/spdlog.h>

std::shared_ptr<Scene> SceneManager::GetOnePolygonScene(EngineServices services)
{
    auto scene = std::make_shared<Scene>(services);

    auto firstMesh = std::make_shared<SimpleMesh>(
        std::vector<glm::vec3>{ 
            {0.0f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
        services.materialFactory->GetMaterial(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
            "./bin/shaders/fragment/const/fragmentShaderSimpleMeshConstant.frag")
    );
    
    auto object = scene->GetSceneServices().gameObjectFactory->GetGameObject("firstMesh", firstMesh);

    object->transform->SetLocalPosition({0, 0, -3.0f});
    object->transform->SetLocalScale(glm::vec3(10.0f));

    scene->Init(std::vector<std::shared_ptr<GameObject>>{object});

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetFourSpheresScene(EngineServices services)
{
    
    auto scene = std::make_shared<Scene>(services);
    auto sphereMesh = scene->GetEngineServices().meshFactory->LoadSphere();

    //auto sphereMesh = scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Moon.obj");
    sphereMesh->GetMaterial()->SetShininess(24);
    sphereMesh->GetMaterial()->SetDiffuse({0.51f, 0.78f, 0.90f});

    auto objects = std::vector<std::shared_ptr<GameObject>>{
            scene->GetSceneServices().gameObjectFactory->GetGameObject("firstSphere", sphereMesh),
            scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", sphereMesh),
            scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", sphereMesh),
            scene->GetSceneServices().gameObjectFactory->GetGameObject("forthSphere", sphereMesh)
    };


    for(auto gameObject : objects)
    {
        gameObject->transform->SetLocalScale(glm::vec3(0.25f));
    }
    objects[0]->transform->SetLocalPosition({0.75, 0.0, 0.0});
    objects[1]->transform->SetLocalPosition({0.0, 0.75, 0.0});
    objects[2]->transform->SetLocalPosition({-0.75, 0.0, 0.0});
    objects[3]->transform->SetLocalPosition({0.0, -0.75, 0.0});

    std::vector<std::unique_ptr<Light>> lights;

    lights.push_back(scene->GetSceneServices().lightFactory->GetPointLight(new Transform(), 
        glm::vec3(1.0f), 2.0f, 0.09f, 0.032f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(1.0f), 0.1f));
    scene->Init(objects, std::move(lights));
    return scene;
}

std::shared_ptr<Scene> SceneManager::GetDifferentShadersScene(EngineServices services)
{

    // Bushes 0
    // Gift 1
    // Plain 2
    // Suzi flat 3
    // Suzi smooth 4
    // Tree 5
    // Sphere 6

    auto scene = std::make_shared<Scene>(services);
    auto lambertMeshes = scene->GetEngineServices().meshFactory->LoadAllPredefinedModels(
        scene->GetEngineServices().materialFactory->GetMaterial(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshLambert.frag"));
    lambertMeshes.push_back(scene->GetEngineServices().meshFactory->LoadSphere(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshLambert.frag"));

    auto constMeshes = scene->GetEngineServices().meshFactory->LoadAllPredefinedModels(
        scene->GetEngineServices().materialFactory->GetMaterial(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/const/fragmentShaderSimpleMeshConstant.frag"));
    constMeshes.push_back(scene->GetEngineServices().meshFactory->LoadSphere(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/const/fragmentShaderSimpleMeshConstant.frag"));

    auto phongMeshes = scene->GetEngineServices().meshFactory->LoadAllPredefinedModels(
        scene->GetEngineServices().materialFactory->GetMaterial(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshPhong.frag"));
    phongMeshes.push_back(scene->GetEngineServices().meshFactory->LoadSphere(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshPhong.frag"));

    auto blinnMeshes = scene->GetEngineServices().meshFactory->LoadAllPredefinedModels(
        scene->GetEngineServices().materialFactory->GetMaterial(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshBlinn.frag"));
    blinnMeshes.push_back(scene->GetEngineServices().meshFactory->LoadSphere(GlobalConfig::GetDefaultSimpleMeshVertexShaderPath(),
        "./bin/shaders/fragment/simplemesh/fragmentShaderSimpleMeshBlinn.frag"));

    auto objects = std::vector<std::shared_ptr<GameObject>>{
        scene->GetSceneServices().gameObjectFactory->GetGameObject("firstSphere", lambertMeshes[2]),
        // Lambert

        scene->GetSceneServices().gameObjectFactory->GetGameObject("firstSphere", lambertMeshes[0]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", lambertMeshes[1]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", lambertMeshes[3]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("forthSphere", lambertMeshes[4]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", lambertMeshes[5]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", lambertMeshes[6]),

        // Const
        scene->GetSceneServices().gameObjectFactory->GetGameObject("firstSphere", constMeshes[0]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", constMeshes[1]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", constMeshes[3]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("forthSphere", constMeshes[4]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", constMeshes[5]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", constMeshes[6]),

        // Phong
        scene->GetSceneServices().gameObjectFactory->GetGameObject("firstSphere", phongMeshes[0]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", phongMeshes[1]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", phongMeshes[3]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("forthSphere", phongMeshes[4]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", phongMeshes[5]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", phongMeshes[6]),

        // Blinn
        scene->GetSceneServices().gameObjectFactory->GetGameObject("firstSphere", blinnMeshes[0]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", blinnMeshes[1]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", blinnMeshes[3]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("forthSphere", blinnMeshes[4]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("secondSphere", blinnMeshes[5]),
        scene->GetSceneServices().gameObjectFactory->GetGameObject("thirdSphere", blinnMeshes[6])
    };


    for(auto gameObject : objects)
    {
        gameObject->transform->SetLocalScale(glm::vec3(0.25f));
    }

    objects[0]->transform->SetLocalScale(glm::vec3(20.0f));

    // Lambert
    objects[1]->transform->SetLocalPosition({0.0, 0.0, 0.0});
    objects[2]->transform->SetLocalPosition({3, 0.0, 0.0});
    objects[3]->transform->SetLocalPosition({6, 0, 0.0});
    objects[4]->transform->SetLocalPosition({9, 0, 0.0});
    objects[5]->transform->SetLocalPosition({12, 0, 0.0});
    objects[6]->transform->SetLocalPosition({15, 0, 0.0});

    objects[1]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[2]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[3]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[4]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[5]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[6]->transform->SetLocalScale(glm::vec3(1.0f));

    // Const
    objects[7]->transform->SetLocalPosition({0.0, 0.0, 5.0});
    objects[8]->transform->SetLocalPosition({3, 0.0, 5.0});
    objects[9]->transform->SetLocalPosition({6, 0, 5.0});
    objects[10]->transform->SetLocalPosition({9, 0, 5.0});
    objects[11]->transform->SetLocalPosition({12, 0, 5.0});
    objects[12]->transform->SetLocalPosition({15, 0, 5.0});

    objects[7]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[8]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[9]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[10]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[11]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[12]->transform->SetLocalScale(glm::vec3(1.0f));

    // Phong
    objects[13]->transform->SetLocalPosition({0.0, 0.0, 10.0});
    objects[14]->transform->SetLocalPosition({3, 0.0, 10.0});
    objects[15]->transform->SetLocalPosition({6, 0, 10.0});
    objects[16]->transform->SetLocalPosition({9, 0, 10.0});
    objects[17]->transform->SetLocalPosition({12, 0, 10.0});
    objects[18]->transform->SetLocalPosition({15, 0, 10.0});

    objects[13]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[14]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[15]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[16]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[17]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[18]->transform->SetLocalScale(glm::vec3(1.0f));

    // Blinn
    objects[19]->transform->SetLocalPosition({0.0, 0.0, 15.0});
    objects[20]->transform->SetLocalPosition({3, 0.0, 15.0});
    objects[21]->transform->SetLocalPosition({6, 0, 15.0});
    objects[22]->transform->SetLocalPosition({9, 0, 15.0});
    objects[23]->transform->SetLocalPosition({12, 0, 15.0});
    objects[24]->transform->SetLocalPosition({15, 0, 15.0});

    objects[19]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[20]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[21]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[22]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[23]->transform->SetLocalScale(glm::vec3(1.0f));
    objects[24]->transform->SetLocalScale(glm::vec3(1.0f));

    std::vector<std::unique_ptr<Light>> lights;

    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(1.0f), 0.5f));
    scene->Init(objects, std::move(lights));
    return scene;
}


std::shared_ptr<Scene> SceneManager::GetForestScene(EngineServices services)
{
    auto scene = std::make_shared<Scene>(services);

    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    std::vector<std::shared_ptr<SimpleMesh>> meshes = scene->GetEngineServices().meshFactory->LoadAllPredefinedModels();
    for(auto mesh : meshes)
    {
        mesh->GetMaterial()->SetShininess(2);
    }

    renderTargets.reserve(meshes.size() + 1);  
    for (auto& mesh : meshes)
    {
        renderTargets.push_back(mesh); 
    }

    std::vector<std::shared_ptr<GameObject>> objects;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distPos(-50.0f, 50.0f);
    std::uniform_real_distribution<float> distScale(0.5f, 1.5f);

    for (int i = 0; i < 500; i++)
    {
        auto tree = scene->GetSceneServices().gameObjectFactory->GetGameObject("tree", renderTargets[5]);
        tree->transform->SetLocalPosition(glm::vec3(distPos(gen), 0.0f, distPos(gen)));
        tree->transform->SetLocalScale(glm::vec3(distScale(gen)));
        tree->transform->SetLocalRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));

        objects.push_back(tree);
    }

    for (int i = 0; i < 2500; i++)
    {
        auto bush = scene->GetSceneServices().gameObjectFactory->GetGameObject("bush", renderTargets[0]);
        bush->transform->SetLocalPosition(glm::vec3(distPos(gen), 0.0f, distPos(gen)));
        bush->transform->SetLocalScale(glm::vec3(distScale(gen) * 2.0f));
        bush->transform->SetLocalRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));

        objects.push_back(bush);
    }

    //auto plane = scene->GetSceneServices().gameObjectFactory->GetGameObject("plain", renderTargets[2]);
    auto plane = scene->GetSceneServices().gameObjectFactory->GetGameObject("plain", 
        scene->GetEngineServices().meshFactory->LoadFromFile("./Models/grass.obj"));
    plane->transform->SetLocalPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    plane->transform->SetLocalScale(glm::vec3(50.0f, 1.0f, 50.0f));
    objects.push_back(plane);

    auto shrekMesh = scene->GetEngineServices().meshFactory->LoadFromFile("./Models/shrek.obj");
    shrekMesh->GetMesh(0)->GetMaterial()->SetShininess(64);
    shrekMesh->GetMesh(0)->GetMaterial()->SetSpecular(glm::vec3(1.0f, 0.0f, 1.0f) * 2.0f );
    auto shrek = scene->GetSceneServices().gameObjectFactory->GetGameObject("plain", shrekMesh);

    shrek->transform->SetLocalPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    shrek->transform->SetLocalScale(glm::vec3(7.0f));
    objects.push_back(shrek);

    auto fionaMesh = scene->GetEngineServices().meshFactory->LoadFromFile("./Models/fiona.obj");
    fionaMesh->GetMesh(0)->GetMaterial()->SetShininess(2);
    auto fiona = scene->GetSceneServices().gameObjectFactory->GetGameObject("plain", fionaMesh);

    fiona->transform->SetLocalPosition(glm::vec3(10.0f, -0.01f, 0.0f));
    fiona->transform->SetLocalScale(glm::vec3(7.0f));
    objects.push_back(fiona);

    std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> heightDist(9.0f, 12.0f);
    std::uniform_real_distribution<float> intensityDist(0.25f, 0.5f);
    std::uniform_real_distribution<float> klDist(0.3f, 0.5f);
    std::uniform_real_distribution<float> kqDist(0.15f, 0.25f);
    std::uniform_real_distribution<float> colorShift(0.8f, 1.0f);

    for (int i = 0; i < 10; i++)
    {
        auto fireflyTransform = new Transform();
        fireflyTransform->SetLocalPosition(glm::vec3(posDist(gen), heightDist(gen), posDist(gen)));

        glm::vec3 color = glm::vec3(1.0f, colorShift(gen), 0.3f + 0.2f * colorShift(gen));

        float intensity = intensityDist(gen);
        float k_l = klDist(gen);
        float k_q = kqDist(gen);

        auto firefly = scene->GetSceneServices().gameObjectFactory->GetFireFly(
            fireflyTransform,
            10.0f,     
            color,
            intensity,
            k_l,
            k_q,
            5.0f  
        );

        objects.push_back(firefly);
    }

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(scene->GetSceneServices().lightFactory->GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(50.0f, 15.0f, 5.0f))}), 
        glm::vec3(1.0f, 0.0f, 0.0f), 11.0f, 0.09f, 0.032f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(-25.0f, 10.0f, -5.0f))}), 
        glm::vec3(0.0f, 1.0f, 1.0f), 2.0f, 0.09f, 0.032f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(0.0f, 10.0f, 0.0f))}), 
        glm::vec3(0.0f, 0.0f, 1.0f), 10.0f, 0.09f, 0.032f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.1f));//glm::vec3(0.05f, 0.05f, 0.1f), 0.1f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetDirectionalLight(
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f), 
        0.1f 
    ));

    lights.push_back(scene->GetSceneServices().lightFactory->GetSpotLight(
        new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(0.0f, 10.0f, 0.0f))}),
        glm::vec3(1.0f, 0.0f, 1.0f),
        20.0f,
        0.09f, 0.032f,
        glm::vec3(0.0f, 0.0f, 1.0f),
        30.0f,
        30.0f));

    scene->Init(objects, std::move(lights));

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetSolarSystemScene(EngineServices services)
{
    auto scene = std::make_shared<Scene>(services);

    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    auto earthModel = scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Earth.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragment/other/fragmentShaderEarth.frag");
    
    earthModel->GetMesh(0)->GetMaterial()->AddColorTexture(scene->GetEngineServices().textureFactory->GetTexture("./Models/2k_earth_nightmap.jpg"));

    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Sun.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragment/const/fragmentShaderMeshConstant.frag"));

    renderTargets.push_back(earthModel);    

    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Moon.obj"));  
    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Login.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragment/const/fragmentShaderMeshConstant.frag" ));  

    std::vector<std::shared_ptr<GameObject>> objects;
    auto sun = scene->GetSceneServices().gameObjectFactory->GetGameObject("Sun", renderTargets[0]);

    std::shared_ptr<Transform> sunTransform = std::make_shared<Transform>();
    auto sunPosition = std::make_shared<Translation>(glm::vec3(0.0f, 2.0f, -10.0f));
    sunTransform->AddBasicTransform(sunPosition);
    sunTransform->AddBasicTransform(std::make_shared<DynamicRotation>(0, glm::vec3(0.0, 0.0, 1.0), 0.5f));
    sun->transform->AddBasicTransform(sunTransform);
    
    auto earth = scene->GetSceneServices().gameObjectFactory->GetGameObject("Earth", renderTargets[1]);
    std::shared_ptr<Transform> earthTransform = std::make_shared<Transform>();

    earthTransform->AddBasicTransform(sunTransform);
    earthTransform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(4.0f, 0.0f, 0.0f)));
    earthTransform->AddBasicTransform(std::make_shared<DynamicRotation>(0, glm::vec3(0.0, 1.0, 0.0), 2.0f));
    earth->transform->AddBasicTransform(earthTransform);
    earth->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.5f)));

    auto moon = scene->GetSceneServices().gameObjectFactory->GetGameObject("Moon", renderTargets[2]);
    moon->transform->AddBasicTransform(earthTransform);
    moon->transform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(2.0f, 0.0f, 0.0f)));
    moon->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.125f)));

    // auto login = scene->GetSceneServices().gameObjectFactory->GetGameObject("Login", renderTargets[3]);
    // login->transform->AddBasicTransform(earthTransform);
    // login->transform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(4.0f, 0.0f, 0.0f)));
    // login->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.25f)));

    // login->transform->AddBasicTransform(sunTransform);
    // login->transform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(4.0f, 0.0f, 0.0f)));
    // login->transform->AddBasicTransform(std::make_shared<DynamicRotation>(0, glm::vec3(0.0, 1.0, 0.0), -2.0f));
    // login->transform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(2.0f, 0.0f, 0.0f)));
    // login->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.125f)));

    objects.push_back(std::shared_ptr<GameObject>(sun));
    objects.push_back(std::shared_ptr<GameObject>(earth));
    objects.push_back(std::shared_ptr<GameObject>(moon));
    //objects.push_back(std::shared_ptr<GameObject>(login));

    std::vector<std::unique_ptr<Light>> lights;
    auto pointLightPosition = new Transform(std::vector<IBasicTransform*>{sunPosition.get()});
    lights.push_back(scene->GetSceneServices().lightFactory->GetPointLight(pointLightPosition, glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, 0.00001f, 0.00001f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(1.0f), 0.1f));

    scene->Init(objects, std::move(lights));

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetWhacAMoleScene(EngineServices services)
{
    auto scene = std::make_shared<Scene>(services);

    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/WhacAMole.obj"));
    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Headcrab.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragment/const/fragmentShaderMeshConstant.frag"));

    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/crowbar.obj"));
    std::vector<std::shared_ptr<GameObject>> objects;
    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/shrek.obj"));

    auto whacAMole = scene->GetSceneServices().gameObjectFactory->GetMachine("Machine");
    whacAMole->transform->SetLocalPosition({0.0f, -2.0f, -3.0f});
    whacAMole->transform->SetLocalRotation(glm::radians(glm::vec3({15.0f, 0.0f, 0.0f})));
    //whacAMole->transform->AddBasicTransform(std::make_shared<DummyTransform>());
    objects.push_back(whacAMole);

    auto crowbar = scene->GetSceneServices().gameObjectFactory->GetGameObject("Crowbar", renderTargets[2]);
    crowbar->transform->SetLocalPosition({0.0f, 3.0f, -5.0f});
    crowbar->transform->SetLocalScale(glm::vec3(2.0f));
    crowbar->transform->AddBasicTransform(std::make_shared<CurvedTranslation>(glm::vec3(0.0f), 1, 1.0f));
    objects.push_back(crowbar);

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(1.0f), 1.0f));

    scene->Init(objects, std::move(lights));
    
    return scene;
}

std::shared_ptr<Scene> SceneManager::GetRacingScene(EngineServices services)
{
    auto scene = std::make_shared<Scene>(services);

    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/Racing/gp.obj"));
    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/ferrari.obj"));

    std::vector<std::shared_ptr<GameObject>> objects;
    auto racingRoad = scene->GetSceneServices().gameObjectFactory->GetGameObject("Racing", renderTargets[0]);

    objects.push_back(racingRoad);

    auto car = scene->GetSceneServices().gameObjectFactory->GetGameObject("Car", renderTargets[1]);
    car->transform->SetLocalPosition({-140.0f, 0.0f, 110.0f});
    car->transform->SetLocalScale(glm::vec3(2.0f));

    std::vector<glm::vec3> points = {
        { -1.0000f, 0.0000f, 46.0048f },  // Anchor
        { -1.5000f, 0.0000f, 46.0048f },  // Left Handle
        { -0.5000f, 0.0000f, 46.0048f },  // Right Handle
        { 1.0000f, 0.0000f, 46.0048f },  // Anchor
        { 0.0000f, 0.0000f, 46.0048f },  // Left Handle
        { 2.0000f, 0.0000f, 46.0048f },  // Right Handle
        { 23.9278f, 0.0000f, 46.0048f },  // Anchor
        { 24.2367f, 0.0000f, 46.0048f },  // Left Handle
        { 23.6188f, 0.0000f, 46.0048f },  // Right Handle
        { 21.7260f, 0.0000f, 46.0048f },  // Anchor
        { 17.9956f, 0.0000f, 46.0048f },  // Left Handle
        { 24.1037f, 0.0000f, 46.0048f },  // Right Handle
        { 25.5387f, 0.0000f, 46.0048f },  // Anchor
        { 23.5782f, 0.0000f, 46.0048f },  // Left Handle
        { 42.0905f, 0.0000f, 46.0048f },  // Right Handle
        { 110.6565f, 0.0000f, 46.0048f },  // Anchor
        { 81.4212f, 0.0000f, 46.0048f },  // Left Handle
        { 113.1906f, 0.0000f, 46.0048f },  // Right Handle
        { 117.0931f, 0.0000f, 46.0048f },  // Anchor
        { 115.7509f, 0.0000f, 46.0048f },  // Left Handle
        { 122.8519f, 0.0000f, 46.0048f },  // Right Handle
        { 113.5364f, 0.0000f, 46.0048f },  // Anchor
        { 122.7443f, 0.0000f, 46.0048f },  // Left Handle
        { 111.7625f, 0.0000f, 46.0048f },  // Right Handle
        { 108.4696f, 0.0000f, 46.0048f },  // Anchor
        { 109.5585f, 0.0000f, 46.0048f },  // Left Handle
        { 102.7001f, 0.0000f, 46.0048f },  // Right Handle
        { 62.5367f, 0.0000f, 46.0048f },  // Anchor
        { 72.7493f, 0.0000f, 46.0048f },  // Left Handle
        { 60.9441f, 0.0000f, 46.0048f },  // Right Handle
        { 59.8751f, 0.0000f, 46.0048f },  // Anchor
        { 60.7501f, 0.0000f, 46.0048f },  // Left Handle
        { 56.8119f, 0.0000f, 46.0048f },  // Right Handle
        { 66.2124f, 0.0000f, 46.0048f },  // Anchor
        { 61.0998f, 0.0000f, 46.0048f },  // Left Handle
        { 71.4579f, 0.0000f, 46.0048f },  // Right Handle
        { 87.4834f, 0.0000f, 46.0048f },  // Anchor
        { 81.9872f, 0.0000f, 46.0048f },  // Left Handle
        { 95.7475f, 0.0000f, 46.0048f },  // Right Handle
        { 122.9937f, 0.0000f, 46.0048f },  // Anchor
        { 117.0266f, 0.0000f, 46.0048f },  // Left Handle
        { 129.9873f, 0.0000f, 46.0048f },  // Right Handle
        { 160.3668f, 0.0000f, 46.0048f },  // Anchor
        { 155.1203f, 0.0000f, 46.0048f },  // Left Handle
        { 171.7043f, 0.0000f, 46.0048f },  // Right Handle
        { 196.1642f, 0.0000f, 46.0048f },  // Anchor
        { 175.2697f, 0.0000f, 46.0048f },  // Left Handle
        { 208.5069f, 0.0000f, 46.0048f },  // Right Handle
        { 266.6294f, 0.0000f, 46.0048f },  // Anchor
        { 254.9850f, 0.0000f, 46.0048f },  // Left Handle
        { 276.9738f, 0.0000f, 46.0048f },  // Right Handle
        { 277.9765f, 0.0000f, 46.0048f },  // Anchor
        { 274.1156f, 0.0000f, 46.0048f },  // Left Handle
        { 283.8063f, 0.0000f, 46.0048f },  // Right Handle
        { 263.5479f, 0.0000f, 46.0048f },  // Anchor
        { 278.2399f, 0.0000f, 46.0048f },  // Left Handle
        { 254.4257f, 0.0000f, 46.0048f },  // Right Handle
        { 231.6154f, 0.0000f, 46.0048f },  // Anchor
        { 242.1528f, 0.0000f, 46.0048f },  // Left Handle
        { 225.2226f, 0.0000f, 46.0048f },  // Right Handle
        { 193.1917f, 0.0000f, 46.0048f },  // Anchor
        { 199.2716f, 0.0000f, 46.0048f },  // Left Handle
        { 180.1416f, 0.0000f, 46.0048f },  // Right Handle
        { 106.2995f, 0.0000f, 46.0048f },  // Anchor
        { 118.2448f, 0.0000f, 46.0048f },  // Left Handle
        { 94.4388f, 0.0000f, 46.0048f },  // Right Handle
        { 65.7002f, 0.0000f, 46.0048f },  // Anchor
        { 77.7224f, 0.0000f, 46.0048f },  // Left Handle
        { 61.6315f, 0.0000f, 46.0048f },  // Right Handle
        { 46.8705f, 0.0000f, 46.0048f },  // Anchor
        { 50.2955f, 0.0000f, 46.0048f },  // Left Handle
        { 44.7705f, 0.0000f, 46.0048f },  // Right Handle
        { 36.3112f, 0.0000f, 46.0048f },  // Anchor
        { 37.7159f, 0.0000f, 46.0048f },  // Left Handle
        { 34.4492f, 0.0000f, 46.0048f },  // Right Handle
        { 27.1402f, 0.0000f, 46.0048f },  // Anchor
        { 29.9344f, 0.0000f, 46.0048f },  // Left Handle
        { 24.8146f, 0.0000f, 46.0048f },  // Right Handle
        { 22.4471f, 0.0000f, 46.0048f },  // Anchor
        { 24.0169f, 0.0000f, 46.0048f },  // Left Handle
        { 20.8772f, 0.0000f, 46.0048f },  // Right Handle

    };

    car->transform->AddBasicTransform(
        std::make_shared<BezierSplineTransform>(points, 0.45f));
    objects.push_back(car);

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(1.0f), 2.0f));

    scene->Init(objects, std::move(lights));

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetBezierScene(EngineServices services)
{
    auto scene = std::make_shared<Scene>(services);

    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    std::vector<std::shared_ptr<SimpleMesh>> meshes = scene->GetEngineServices().meshFactory->LoadAllPredefinedModels();
    renderTargets.reserve(meshes.size() + 1);  
    for (auto& mesh : meshes)
    {
        renderTargets.push_back(mesh); 
    }
    renderTargets.push_back(scene->GetEngineServices().meshFactory->LoadFromFile("./Models/ferrari.obj"));
    std::vector<std::shared_ptr<GameObject>> objects;

    auto plane = scene->GetSceneServices().gameObjectFactory->GetGameObject("plain", renderTargets[2]);
    plane->transform->SetLocalPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    plane->transform->SetLocalScale(glm::vec3(50.0f, 1.0f, 50.0f));
    objects.push_back(std::shared_ptr<GameObject>(plane));

    auto car = scene->GetSceneServices().gameObjectFactory->GetGameObject("Car", renderTargets[meshes.size() ]);
    car->transform->SetLocalScale(glm::vec3(1.0f));

    objects.push_back(car);

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(scene->GetSceneServices().lightFactory->GetAmbientLight(glm::vec3(0.05f, 0.05f, 0.1f), 0.1f));
    lights.push_back(scene->GetSceneServices().lightFactory->GetDirectionalLight(
        glm::vec3(0.6f, 0.7f, 1.0f),
        glm::vec3(-0.3f, -1.0f, -0.5f), 
        1.0f 
    ));

    scene->Init(objects, std::move(lights));

    return scene;
}
