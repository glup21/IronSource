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

std::shared_ptr<Scene> SceneManager::GetOnePolygonScene()
{
    auto firstMesh = std::make_shared<SimpleMesh>(
        std::vector<glm::vec3>{ 
            {0.0f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
        std::vector<glm::vec3>{ {1.0f, 0, 0}, {0, 1.0f, 0}, {0, 0, 1.0f} },
        MaterialFactory::GetMaterial()
    );
    
    auto object = GameObjectFactory::GetInstance().GetGameObject("firstMesh", firstMesh);

    object->transform->SetLocalPosition({0, 0, -3.0f});
    object->transform->AddBasicTransform(std::make_shared<DynamicRotation>(0, glm::vec3(0.0, 0.0, 1.0), 10.0f));
    object->transform->SetLocalScale(glm::vec3(10.0f));
    auto scene = std::make_shared<Scene>
    (
        std::vector<std::shared_ptr<GameObject>>{object}
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetFourSpheresScene()
{
    auto sphereMesh = MeshFactory::GetInstance().LoadSphere();

    auto gameObjects = std::vector<std::shared_ptr<GameObject>>{
            GameObjectFactory::GetInstance().GetGameObject("firstSphere", sphereMesh),
            GameObjectFactory::GetInstance().GetGameObject("secondSphere", sphereMesh),
            GameObjectFactory::GetInstance().GetGameObject("thirdSphere", sphereMesh),
            GameObjectFactory::GetInstance().GetGameObject("forthSphere", sphereMesh),
    };

    for(auto gameObject : gameObjects)
    {
        gameObject->transform->SetLocalScale(glm::vec3(0.25f));
    }
    gameObjects[0]->transform->SetLocalPosition({1.0, 0.0, 0.0});
    gameObjects[1]->transform->SetLocalPosition({0.0, 1.0, 0.0});
    gameObjects[2]->transform->SetLocalPosition({-1.0, 0.0, 0.0});
    gameObjects[3]->transform->SetLocalPosition({0.0, -1.0, 0.0});

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(LightFactory::GetInstance().GetPointLight(new Transform(), 
        glm::vec3(1.0f), 1.0f, 0.09f, 0.032f));
    lights.push_back(LightFactory::GetInstance().GetAmbientLight(glm::vec3(0.05f, 0.05f, 0.1f), 0.1f));
    auto scene = std::make_shared<Scene>
    (
        gameObjects,
        std::move(lights)
    );

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetForestScene()
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    std::vector<std::shared_ptr<SimpleMesh>> meshes = MeshFactory::GetInstance().LoadAllPredefinedModels();
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
        auto tree = GameObjectFactory::GetInstance().GetGameObject("tree", renderTargets[5]);
        tree->transform->SetLocalPosition(glm::vec3(distPos(gen), 0.0f, distPos(gen)));
        tree->transform->SetLocalScale(glm::vec3(distScale(gen)));
        tree->transform->SetLocalRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));

        objects.push_back(tree);
    }

    for (int i = 0; i < 2500; i++)
    {
        auto bush = GameObjectFactory::GetInstance().GetGameObject("bush", renderTargets[0]);
        bush->transform->SetLocalPosition(glm::vec3(distPos(gen), 0.0f, distPos(gen)));
        bush->transform->SetLocalScale(glm::vec3(distScale(gen) * 2.0f));
        bush->transform->SetLocalRotation(glm::vec3(0.0f, distPos(gen) * 36.0f, 0.0f));

        objects.push_back(bush);
    }

    auto plane = GameObjectFactory::GetInstance().GetGameObject("plain", renderTargets[2]);
    plane->transform->SetLocalPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    plane->transform->SetLocalScale(glm::vec3(50.0f, 1.0f, 50.0f));
    objects.push_back(plane);

    std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> heightDist(9.0f, 12.0f);
    std::uniform_real_distribution<float> intensityDist(0.5f, 0.75f);
    std::uniform_real_distribution<float> klDist(0.2f, 0.4f);
    std::uniform_real_distribution<float> kqDist(0.08f, 0.15f);
    std::uniform_real_distribution<float> colorShift(0.8f, 1.0f);

    for (int i = 0; i < 10; i++)
    {
        auto fireflyTransform = new Transform();
        fireflyTransform->SetLocalPosition(glm::vec3(posDist(gen), heightDist(gen), posDist(gen)));

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

        objects.push_back(firefly);
    }

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(LightFactory::GetInstance().GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(35.0f, 15.0f, 5.0f))}), 
        glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f));
    lights.push_back(LightFactory::GetInstance().GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(-25.0f, 10.0f, -5.0f))}), 
        glm::vec3(0.0f, 1.0f, 1.0f), 2.0f, 0.09f, 0.032f));
    lights.push_back(LightFactory::GetInstance().GetPointLight(new Transform(std::vector<IBasicTransform*>{new Translation(glm::vec3(0.0f, 10.0f, 0.0f))}), 
        glm::vec3(0.0f, 0.0f, 1.0f), 3.0f, 0.09f, 0.032f));
    lights.push_back(LightFactory::GetInstance().GetAmbientLight(glm::vec3(1.0f, 0.0f, 0.0f), 0.1f));//glm::vec3(0.05f, 0.05f, 0.1f), 0.1f));
    // lights.push_back(LightFactory::GetInstance().GetDirectionalLight(
    //     glm::vec3(0.6f, 0.7f, 1.0f),
    //     glm::vec3(-0.3f, -1.0f, -0.5f), 
    //     0.025f 
    // ));

    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetSolarSystemScene()
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    auto earthModel = MeshFactory::GetInstance().LoadFromFile("./Models/Earth.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragmentShaderEarth.frag");
    
    earthModel->GetMesh(0)->GetMaterial()->AddColorTexture(TextureFactory::GetInstance().GetTexture("./Models/2k_earth_nightmap.jpg"));

    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/Sun.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragmentShaderMeshConstant.frag"));

    renderTargets.push_back(earthModel);    

    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/Moon.obj"));  
    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/Login.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragmentShaderMeshConstant.frag" ));  

    std::vector<std::shared_ptr<GameObject>> objects;


    auto sun = GameObjectFactory::GetInstance().GetGameObject("Sun", renderTargets[0]);

    std::shared_ptr<Transform> sunTransform = std::make_shared<Transform>();
    auto sunPosition = std::make_shared<Translation>(glm::vec3(0.0f, 2.0f, -10.0f));
    sunTransform->AddBasicTransform(sunPosition);
    sunTransform->AddBasicTransform(std::make_shared<DynamicRotation>(0, glm::vec3(0.0, 0.0, 1.0), 0.5f));
    sun->transform->AddBasicTransform(sunTransform);
    
    auto earth = GameObjectFactory::GetInstance().GetGameObject("Earth", renderTargets[1]);
    std::shared_ptr<Transform> earthTransform = std::make_shared<Transform>();

    earthTransform->AddBasicTransform(sunTransform);
    earthTransform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(4.0f, 0.0f, 0.0f)));
    earthTransform->AddBasicTransform(std::make_shared<DynamicRotation>(0, glm::vec3(0.0, 1.0, 0.0), 2.0f));
    earth->transform->AddBasicTransform(earthTransform);
    earth->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.5f)));

    auto moon = GameObjectFactory::GetInstance().GetGameObject("Moon", renderTargets[2]);
    moon->transform->AddBasicTransform(earthTransform);
    moon->transform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(2.0f, 0.0f, 0.0f)));
    moon->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.125f)));

    auto login = GameObjectFactory::GetInstance().GetGameObject("Login", renderTargets[3]);
    login->transform->AddBasicTransform(earthTransform);
    login->transform->AddBasicTransform(std::make_shared<Translation>(glm::vec3(4.0f, 0.0f, 0.0f)));
    login->transform->AddBasicTransform(std::make_shared<Scale>(glm::vec3(0.25f)));

    objects.push_back(std::shared_ptr<GameObject>(sun));
    objects.push_back(std::shared_ptr<GameObject>(earth));
    objects.push_back(std::shared_ptr<GameObject>(moon));
    objects.push_back(std::shared_ptr<GameObject>(login));

    std::vector<std::unique_ptr<Light>> lights;
    auto pointLightPosition = new Transform(std::vector<IBasicTransform*>{sunPosition.get()});
    lights.push_back(LightFactory::GetInstance().GetPointLight(pointLightPosition, glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, 0.00001f, 0.00001f));
    lights.push_back(LightFactory::GetInstance().GetAmbientLight(glm::vec3(1.0f), 0.1f));

    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetWhacAMoleScene()
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/WhacAMole.obj"));
    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/Headcrab.obj", GlobalConfig::GetDefaultMeshVertexShaderPath(),
        "./bin/shaders/fragmentShaderMeshConstant.frag"));

    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/crowbar.obj"));
    std::vector<std::shared_ptr<GameObject>> objects;
    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/shrek.obj"));

    auto whacAMole = GameObjectFactory::GetInstance().GetMachine("Machine");
    whacAMole->transform->SetLocalPosition({0.0f, -2.0f, -3.0f});
    whacAMole->transform->SetLocalRotation(glm::radians(glm::vec3({15.0f, 0.0f, 0.0f})));
    //whacAMole->transform->AddBasicTransform(std::make_shared<DummyTransform>());
    objects.push_back(whacAMole);

    auto crowbar = GameObjectFactory::GetInstance().GetGameObject("Crowbar", renderTargets[2]);
    crowbar->transform->SetLocalPosition({0.0f, 3.0f, -5.0f});
    crowbar->transform->SetLocalScale(glm::vec3(2.0f));
    crowbar->transform->AddBasicTransform(std::make_shared<CurvedTranslation>(glm::vec3(0.0f), 1, 1.0f));
    objects.push_back(crowbar);

    auto shrek = GameObjectFactory::GetInstance().GetGameObject("Shrek", renderTargets[3]);
    shrek->transform->SetLocalPosition({0.0f, 3.0f, -5.0f});
    shrek->transform->SetLocalScale(glm::vec3(1.0f));

    std::vector<glm::vec3> path =
    {
        { -1.0000f,  0.0000f, -0.0000f }, // Control point
        { -1.0315f, -0.7293f, -0.0000f }, // Handle LEFT
        { -0.9695f,  0.7054f, -0.0000f }, // Handle RIGHT

        {  1.0000f,  0.0000f, -0.0000f },
        {  1.1835f, -0.8823f, -0.0000f },
        {  0.8109f,  0.9096f, -0.0000f },

        { 0.9712f, 1.2836f, 0.0000f },
        { 0.0622f, 1.2817f, 0.0000f },
        { 1.9461f, 1.2856f, 0.0000f },

        { 1.7982f, -0.3968f, -0.4020f },
        { 1.5226f,  0.1633f, -0.2680f },
        { 2.0739f, -0.9569f, -0.5361f },
    };


    shrek->transform->AddBasicTransform(
        std::make_shared<BezierSplineTransform>(path, 0.2f));

    objects.push_back(shrek);

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(LightFactory::GetInstance().GetAmbientLight(glm::vec3(1.0f), 1.0f));

    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    // Need to resolve this issue, because right now for an object to delete any other object it requires pointer to a Scene,
    // which is bad design
    whacAMole->SetScene(scene.get());

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetRacingScene()
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/Racing/gp.obj"));
    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/Car/Untitled.obj"));

    std::vector<std::shared_ptr<GameObject>> objects;
    auto racingRoad = GameObjectFactory::GetInstance().GetGameObject("Racing", renderTargets[0]);
    //racingRoad->transform->SetLocalPosition({20.0f, -5.0f, -100.0f});
    //racingRoad->transform->SetLocalScale(glm::vec3(0.5f));
    objects.push_back(racingRoad);

    auto car = GameObjectFactory::GetInstance().GetGameObject("Car", renderTargets[1]);
    car->transform->SetLocalPosition({-140.0f, 0.0f, 110.0f});
    car->transform->SetLocalScale(glm::vec3(2.0f));

    std::vector<glm::vec3> points = {
        {-1.0000f, 0.0f, 0.0000f},
        {-1.5000f, 0.0f, 0.0000f},
        {-0.5000f, 0.0f, 0.0000f},

        {1.0000f, 0.0f, 0.0000f},
        {0.0000f, 0.0f, 0.0000f},
        {2.0000f, 0.0f, 0.0000f},

        {-2.7021f, 0.0f, -0.0778f},
        {-0.0820f, 0.0f, 0.1377f},
        {-5.3222f, 0.0f, -0.2932f},

        {-14.1975f, 0.0f, -0.7580f},
        {-12.4807f, 0.0f, -1.8427f},
        {-18.5180f, 0.0f, 1.9717f},

        {-33.9178f, 0.0f, -0.7623f},
        {-29.6267f, 0.0f, -3.3122f},
        {-45.3594f, 0.0f, 6.0368f},

        {-90.4967f, 0.0f, -0.5267f},
        {-74.1399f, 0.0f, -7.5856f},
        {-98.1000f, 0.0f, 2.7546f},

        {-124.8200f, 0.0f, 0.1598f},
        {-117.5200f, 0.0f, -2.9195f},
        {-132.6367f, 0.0f, 3.4571f},

        {-144.5949f, 0.0f, -1.2005f},
        {-144.1417f, 0.0f, -2.0989f},
        {-144.6700f, 0.0f, -1.0517f},

        {-134.8671f, 0.0f, 0.0496f},
        {-137.8262f, 0.0f, 0.9374f},
        {-128.1568f, 0.0f, -1.9638f},

        {-90.7427f, 0.0f, -0.7970f},
        {-97.3963f, 0.0f, 1.4098f},
        {-83.8675f, 0.0f, -3.0774f},

        {-65.8677f, 0.0f, -0.0831f},
        {-71.3416f, 0.0f, -0.8252f},
        {-61.7659f, 0.0f, 0.4730f},

        {-63.9821f, 0.0f, -0.0386f},
        {-59.2863f, 0.0f, -2.2722f},
        {-67.3640f, 0.0f, 1.5700f},

        {-83.7610f, 0.0f, -1.0543f},
        {-79.9601f, 0.0f, -2.4329f},
        {-96.8070f, 0.0f, 3.6776f},

        {-141.3524f, 0.0f, -0.5923f},
        {-129.1272f, 0.0f, -4.4936f},
        {-146.9824f, 0.0f, 1.2043f},

        {-164.4589f, 0.0f, -1.0275f},
        {-159.8462f, 0.0f, -3.0221f},
        {-172.7358f, 0.0f, 2.5517f},

        {-169.5144f, 0.0f, -1.0494f},
        {-169.2276f, 0.0f, -0.5790f},
        {-169.9998f, 0.0f, -1.8457f},

        {-145.7054f, 0.0f, -1.1124f},
        {-163.5978f, 0.0f, -2.5843f},
        {-138.9315f, 0.0f, -0.5551f},

        {-125.2594f, 0.0f, -0.2538f},
        {-132.3335f, 0.0f, 2.0272f},
        {-109.2652f, 0.0f, -5.4113f},

        {-31.3218f, 0.0f, -0.5317f},
        {-46.9226f, 0.0f, 5.7066f},
        {-28.9376f, 0.0f, -1.4851f},

        {-15.1054f, 0.0f, -0.4058f},
        {-16.7166f, 0.0f, -1.3350f},
        {-10.2646f, 0.0f, 2.3861f},

        {6.9189f, 0.0f, -0.6972f},
        {1.3071f, 0.0f, -1.2485f},
        {20.2232f, 0.0f, 0.6098f},

        {60.2647f, 0.0f, -0.7345f},
        {47.6281f, 0.0f, 3.0735f},
        {65.6241f, 0.0f, -2.3496f},

        {86.5528f, 0.0f, -0.1852f},
        {81.9425f, 0.0f, 2.1598f},
        {90.2686f, 0.0f, -2.0751f},

        {97.0321f, 0.0f, -0.2718f},
        {97.5796f, 0.0f, 0.3885f},
        {96.6629f, 0.0f, -0.7171f},

        {99.1138f, 0.0f, -0.3322f},
        {98.5474f, 0.0f, -0.5037f},
        {102.5618f, 0.0f, 0.7118f},

        {79.1959f, 0.0f, -0.7362f},
        {92.0682f, 0.0f, 0.0239f},
        {75.1223f, 0.0f, -0.9767f},

        {58.6171f, 0.0f, -0.4535f},
        {64.0189f, 0.0f, -0.0094f},
        {50.7144f, 0.0f, -1.1031f},

        {25.5166f, 0.0f, 0.0256f},
        {34.1591f, 0.0f, 0.8750f},
        {17.6552f, 0.0f, -0.7470f},

        {0.7101f, 0.0f, -0.3158f},
        {5.4651f, 0.0f, 0.3953f},
        {-1.5762f, 0.0f, -0.6577f},

        {-6.3939f, 0.0f, 0.2674f},
        {-2.9377f, 0.0f, 0.5517f},
        {-9.8500f, 0.0f, -0.0170f},
    };

    car->transform->AddBasicTransform(
        std::make_shared<BezierSplineTransform>(points, 0.45f));
    objects.push_back(car);

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(LightFactory::GetInstance().GetAmbientLight(glm::vec3(1.0f), 2.0f));

    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    return scene;
}

std::shared_ptr<Scene> SceneManager::GetBezierScene()
{
    std::vector<std::shared_ptr<IRenderTarget>> renderTargets;

    std::vector<std::shared_ptr<SimpleMesh>> meshes = MeshFactory::GetInstance().LoadAllPredefinedModels();
    renderTargets.reserve(meshes.size() + 1);  
    for (auto& mesh : meshes)
    {
        renderTargets.push_back(mesh); 
    }
    renderTargets.push_back(MeshFactory::GetInstance().LoadFromFile("./Models/shrek.obj"));
    std::vector<std::shared_ptr<GameObject>> objects;

    auto plane = GameObjectFactory::GetInstance().GetGameObject("plain", renderTargets[2]);
    plane->transform->SetLocalPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    plane->transform->SetLocalScale(glm::vec3(50.0f, 1.0f, 50.0f));
    objects.push_back(std::shared_ptr<GameObject>(plane));

    auto car = GameObjectFactory::GetInstance().GetGameObject("Car", renderTargets[meshes.size() ]);
    car->transform->SetLocalScale(glm::vec3(2.0f));

    objects.push_back(car);

    std::vector<std::unique_ptr<Light>> lights;
    lights.push_back(LightFactory::GetInstance().GetAmbientLight(glm::vec3(0.05f, 0.05f, 0.1f), 0.1f));
    lights.push_back(LightFactory::GetInstance().GetDirectionalLight(
        glm::vec3(0.6f, 0.7f, 1.0f),
        glm::vec3(-0.3f, -1.0f, -0.5f), 
        1.0f 
    ));

    auto scene = std::make_shared<Scene>(objects, std::move(lights));

    return scene;
}
