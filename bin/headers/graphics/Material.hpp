#pragma once
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Texture.hpp"
#include <memory>

class Material
{
private:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Texture> colorTexture;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess; 

public:
    Material(std::shared_ptr<ShaderProgram> shaderProgram, glm::vec3 ambient = glm::vec3(1.0),
        glm::vec3 diffuse = glm::vec3(1.0), glm::vec3 specular = glm::vec3(1.0), float shininess = 1.0);
    ~Material() = default;

    void Use();
    void SetTransformMatrix(glm::mat4 transformMatrix);

    void SetColorTexture(std::shared_ptr<Texture> texture);
};