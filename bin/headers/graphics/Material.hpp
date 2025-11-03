#pragma once
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Texture.hpp"
#include <memory>

class Material
{
private:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Texture> colorTexture;
public:
    Material(std::shared_ptr<ShaderProgram> shaderProgram);
    ~Material() = default;

    void Use();
    void SetTransformMatrix(glm::mat4 transformMatrix);

    void SetColorTexture(std::shared_ptr<Texture> texture);
};