#include <random>
#include "headers/gameobject/WhacAMole.hpp"
#include "headers/services/GameObjectFactory.hpp"
#include "headers/gamelogic/Scene.hpp"
#include "headers/transform/DynamicTranslation.hpp"
#include "headers/transform/CurvedTranslation.hpp"

static std::random_device rd;
static std::mt19937 rng(rd());

WhacAMole::WhacAMole(std::string name, std::shared_ptr<IRenderTarget> renderTarget, int id)
    : GameObject(name, renderTarget, id)
{
    holes = {
        {-0.75f, 2.5f, 0.75f},
        {-0.25f, 2.5f, 0.75f},
        { 0.25f, 2.5f, 0.75f},
        { 0.75f, 2.5f, 0.75f},

        {-0.75f, 2.5f, 1.2f},
        {-0.25f, 2.5f, 1.2f},
        { 0.25f, 2.5f, 1.2f},
        { 0.75f, 2.5f, 1.2f}
    };

    hitTime = 0.5f;           
    timer = hitTime;
    spawnInterval = 0.5f;     
    moleVisible = false;
}

void WhacAMole::Update(float deltaTime)
{
    timer -= deltaTime;

    if (!moleVisible && timer <= 0.0f)
    {
        std::uniform_int_distribution<int> holeDist(0, holes.size() - 1);
        int index = holeDist(rng);

        std::uniform_real_distribution<float> heightDist(0.5f, 1.0f);
        float height = heightDist(rng);

        std::uniform_real_distribution<float> speedDist(0.8f, 3.0f);
        float speed = speedDist(rng);

        float animTime = height / speed;


        hitTime = animTime + 0.5f; 

        SpawnMole(holes[index], height, speed);

        moleVisible = true;
        timer = hitTime;
    }
    else if (moleVisible && timer <= 0.0f)
    {
        RemoveMole();

        moleVisible = false;
        timer = spawnInterval;
        hitTime = 0.5f;
    }
}

void WhacAMole::SpawnMole(glm::vec3 position, float height, float speed)
{
    mole = GameObjectFactory::GetInstance().GetMole();

    mole->transform->SetLocalRotation(glm::radians(glm::vec3{15.0f, 0.0f, 0.0f}));
    mole->transform->SetLocalScale(glm::vec3{1.0f});
    mole->transform->SetLocalPosition(transform->GetLocalPosition() + position);

    std::uniform_int_distribution<int> movementDist(0, 1);

    if(movementDist(rng))
    {
        mole->transform->AddBasicTransform(
            std::make_shared<DynamicTranslation>(
                glm::vec3(0.0f),
                glm::vec3(0.0f, height, 0.0f),
                speed
            )
        );
    }
    else
    {
        std::uniform_int_distribution<int> directionDist (0, 1);
        mole->transform->AddBasicTransform(std::make_shared<CurvedTranslation>(
            glm::vec3(-1.0f, 0.0f, 0.0f),
            0.25,
            speed,
            directionDist(rng) ? CLOCKWISE : COUNTER_CLOCKWISE));
    }

    mole->SetIsDestructable(true);
    scene->AddGameObject(mole);
}

void WhacAMole::RemoveMole()
{ 
    scene->DeleteGameObject(mole->GetId());
    mole = nullptr;
}