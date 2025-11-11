#pragma once
#include "headers/interfaces/IRenderTarget.hpp"

class ShaderProgram;

class Skybox: public IRenderTarget
{
public:
    Skybox(std::vector<glm::vec3> vertices, std::vector<std::string> faces, std::shared_ptr<ShaderProgram> shaderProgram);
    void Render(glm::mat4 transformMatrix) override;
    void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

private:
    GLuint cubemapTextureID;
    GLuint VAO, VBO;

    std::vector<glm::vec3> vertices;
    size_t vertexCount;

    std::shared_ptr<ShaderProgram> shaderProgram;

    void InitMesh();
    void InitCubemap(std::vector<std::string> faces);
};