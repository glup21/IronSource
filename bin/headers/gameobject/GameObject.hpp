#pragma once
#include <memory>
#include <string>

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/services/ShaderLibrary.hpp"
#include "headers/transform/Transform.hpp"

class GameObject
{
protected:
    std::shared_ptr<IRenderTarget> renderTarget;
    std::string name;
    std::unique_ptr<Transform> transform;
public:
    GameObject(std::string name, IRenderTarget* renderTarget, Transform* transform);
    GameObject(std::string name, Transform* transform);
    ~GameObject() = default;

    void Update();
    void Render();
};