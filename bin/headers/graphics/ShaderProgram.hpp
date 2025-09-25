#pragma once
#include "headers/graphics/Shader.hpp"
#include <vector>
#include <memory>

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
};