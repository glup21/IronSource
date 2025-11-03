#include "headers/graphics/Material.hpp"

Material::Material(std::shared_ptr<ShaderProgram> shaderProgram) : shaderProgram(shaderProgram)
{

}

void Material::Use()
{
    this->shaderProgram->Use();
}

void Material::SetTransformMatrix(glm::mat4 transformMatrix)
{
    this->shaderProgram->SetUniform("transformMatrix", transformMatrix);
}

void Material::SetColorTexture(std::shared_ptr<Texture> texture)
{
    this->colorTexture = texture;
}