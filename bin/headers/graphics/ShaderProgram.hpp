#pragma once
#include "headers/graphics/Shader.hpp"
#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>

class ShaderProgram
{
private:
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> fragmentShader;

    GLuint shaderProgramId;

public:
    ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

    void LinkShaderProgram();
    void UseShaderProgram();

    void SetUniform(std::string name, glm::mat4 matrix4);
};