#pragma once
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Texture.hpp"
#include <memory>

class Material
{
private:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::vector<std::shared_ptr<Texture>> colorTexture;
    std::shared_ptr<Texture> normalTexture;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
public:
    Material(std::shared_ptr<ShaderProgram> shaderProgram, glm::vec3 ambient = glm::vec3(1.0),
        glm::vec3 diffuse = glm::vec3(1.0), glm::vec3 specular = glm::vec3(1.0), float shininess = 64.0);
    ~Material() = default;

    void Use();
    void SetTransformMatrix(glm::mat4 transformMatrix);

    void AddColorTexture(std::shared_ptr<Texture> texture);
    void SetNormalTexture(std::shared_ptr<Texture> texture);

    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);
    void SetShininess(float shininess);
};