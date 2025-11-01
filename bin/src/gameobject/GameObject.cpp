#include "headers/gameobject/GameObject.hpp"
#include <utility> 

GameObject::GameObject(std::string name, IRenderTarget* renderTarget, Transform* transform) : 
    name(name), renderTarget(renderTarget), transform(transform)
{

}

GameObject::GameObject(std::string name, Transform* transform) : 
    name(name), transform(transform)
{

}


void GameObject::Update()
{
    // Game logic here
}

void GameObject::Render()
{
    if(renderTarget != nullptr && transform != nullptr)
    {
        glm::mat4 modelMatrix = transform->GetTransformMatrix();
        renderTarget->Render(modelMatrix); 
    }
}
