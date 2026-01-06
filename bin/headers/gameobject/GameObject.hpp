#pragma once
#include <memory>
#include <string>

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/transform/Transform.hpp"

class Scene;
class GameObject
{
protected:

    std::shared_ptr<IRenderTarget> renderTarget;
    std::string name;
    int id;

    bool isDestructable = false;
public:
    std::unique_ptr<Transform> transform;

    GameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, Transform* transform, int id);
    GameObject(std::string name, std::shared_ptr<IRenderTarget> renderTarget, int id);
    GameObject(std::string name, Transform* transform, int id);
    ~GameObject() = default;

    virtual void Update(float deltaTime);
    void Render();

    IRenderTarget* GetRenderTarget();

    int GetId() { return id; }
    void SetIsDestructable(bool value) { isDestructable = value; } 
    bool GetIsDestructable() { return isDestructable; }
    std::string GetName();
};