#include "headers/gameobject/GameObject.hpp"
#include <utility> 

GameObject::GameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, Transform* transform, int id) : 
    name(name), renderTarget(renderTarget), transform(transform), id(id)
{

}

GameObject::GameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, int id) : 
    name(name), renderTarget(renderTarget), transform(std::make_unique<Transform>()), id(id)
{

}


GameObject::GameObject(std::string name, Transform* transform, int id) : 
    name(name), transform(transform), id(id)
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
        // IDs are clamped to 255 though
        glStencilFunc(GL_ALWAYS, id, 0xFF);
        glm::mat4 modelMatrix = transform->GetTransformMatrix();
        renderTarget->Render(modelMatrix); 
    }
}

IRenderTarget* GameObject::GetRenderTarget()
{
    return renderTarget.get();
}

std::string GameObject::GetName()
{
    return name;
}