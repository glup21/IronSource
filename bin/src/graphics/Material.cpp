#include "headers/graphics/Material.hpp"

Material::Material(std::shared_ptr<ShaderProgram> shaderProgram, glm::vec3 ambient,
                   glm::vec3 diffuse, glm::vec3 specular, float shininess)
    : shaderProgram(shaderProgram), ambient(ambient), diffuse(diffuse), specular(specular),
      shininess(shininess)
{
     //this->diffuse = glm::vec3(0.0f, 0.0f, 1.0f);
     //this->shininess = 128;
}

void Material::Use()
{
    this->shaderProgram->Use();

    if (colorTexture.size() > 1)
    {
        // Its only used on Earth for blend essentially
        for (int i = 0; i < colorTexture.size(); i++)
        {
            this->colorTexture[i]->Use(GL_TEXTURE0 + i);
            this->shaderProgram->SetUniform("colorTextures[" + std::to_string(i) + "]", i);
        }
    }
    else if (colorTexture.size() == 1)
    {
        this->colorTexture[0]->Use(GL_TEXTURE0);
        this->shaderProgram->SetUniform("colorTexture", 0);
    }

    if (normalTexture)
    {
        this->normalTexture->Use(GL_TEXTURE0 + colorTexture.size());
        this->shaderProgram->SetUniform("normalTexture", 0);
    }

    this->shaderProgram->SetUniform("materialAmbient", this->ambient);
    this->shaderProgram->SetUniform("materialDiffuse", this->diffuse);
    this->shaderProgram->SetUniform("materialSpecular", this->specular);
    this->shaderProgram->SetUniform("materialShininess", this->shininess);
    this->shaderProgram->SetUniform("time", static_cast<float>(glfwGetTime()));
}

void Material::SetTransformMatrix(glm::mat4 transformMatrix)
{
    this->shaderProgram->SetUniform("transformMatrix", transformMatrix);
}

void Material::AddColorTexture(std::shared_ptr<Texture> texture)
{
    this->colorTexture.push_back(texture);
}

void Material::SetNormalTexture(std::shared_ptr<Texture> texture)
{
    this->normalTexture = texture;
}

void Material::SetAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}

void Material::SetDiffuse(glm::vec3 diffuse)
{
    this->diffuse = diffuse;
}

void Material::SetSpecular(glm::vec3 specular)
{
    this->specular = specular;
}

void Material::SetShininess(float shininess)
{
    this->shininess = shininess;
}