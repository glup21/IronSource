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


void GameObject::Update(float debug)
{
    // Game logic here
}

void GameObject::Render()
{
    if(renderTarget != nullptr && transform != nullptr)
    {
        glm::mat4 modelMatrix = transform->GetWorldMatrix();
        renderTarget->Render(modelMatrix); 
    }
}

IRenderTarget* GameObject::GetRenderTarget()
{
    return renderTarget.get();
}
