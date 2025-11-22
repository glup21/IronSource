#include "headers/gameobject/WhacAMole.hpp"
#include "headers/services/GameObjectFactory.hpp"
#include "headers/gamelogic/Scene.hpp"
#include "headers/transform/DynamicTranslation.hpp"

WhacAMole::WhacAMole(std::string name, std::shared_ptr<IRenderTarget> renderTarget, int id)
    : GameObject(name, renderTarget, id)
{
    holes = {
        glm::vec3(-0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    };

    hitTime = 1.0f;
    timer = hitTime;
    spawnInterval = 2.0f;
    moleVisible = false;
    
}

void WhacAMole::Update(float deltaTime)
{
    timer -= deltaTime;

    if (!moleVisible && timer <= 0.0f)
    {
        int index = rand() % holes.size();
        SpawnMole(holes[index]);

        moleVisible = true;
        timer = hitTime; 
    }
    else if (moleVisible && timer <= 0.0f)
    {
        RemoveMole();

        moleVisible = false;
        timer = spawnInterval; 
    }
}


void WhacAMole::SpawnMole(glm::vec3 position)
{
    mole = GameObjectFactory::GetInstance().GetMole();
    mole->transform->SetLocalRotation(glm::radians(glm::vec3({15.0f, 0.0f, 0.0f})));
    mole->transform->SetLocalScale(glm::vec3{2.0f});
    //mole->transform->SetLocalPosition(transform->GetLocalPosition());
    mole->transform->AddBasicTransform(std::make_shared<DynamicTranslation>(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.1f));
    mole->SetIsDestructable(true);
    scene->AddGameObject(mole);
}

void WhacAMole::RemoveMole()
{
    scene->DeleteGameObject(mole->GetId());
    mole = nullptr;
}