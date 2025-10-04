#pragma once

#include <string>
#include "headers/graphics/ShaderProgram.hpp"
#include <memory>
#include "headers/services/ShaderLibrary.hpp"
#include <glm/mat4x4.hpp>
// I work with C#, so I am used to calling it interface :D
class IRenderTarget
{
public:
    virtual ~IRenderTarget() = default;

    virtual void Render(glm::mat4 transformMatrix) = 0;
    virtual void Init(ShaderLibrary* shaderLibrary, std::string vertexShader, std::string fragmentShader) = 0;

private:
    std::shared_ptr<ShaderProgram> shaderProgram;
};