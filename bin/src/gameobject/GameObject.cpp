#include "headers/gameobject/GameObject.hpp"
#include <utility> 

GameObject::GameObject(std::string name, IRenderTarget* renderTarget) : 
    name(name), renderTarget(renderTarget) 
{

}

void GameObject::Update()
{
    // Game logic here
}

void GameObject::Render()
{
    if(this->renderTarget.get() != nullptr)
        this->renderTarget->Render();
}