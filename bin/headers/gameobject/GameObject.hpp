#pragma once
#include <memory>
#include <string>

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/services/ShaderLibrary.hpp"

class GameObject
{
private:
    std::shared_ptr<IRenderTarget> renderTarget;
    std::string name;
public:
    GameObject(std::string name, IRenderTarget* renderTarget);
    ~GameObject() = default;

    void Update();
    void Render();
};