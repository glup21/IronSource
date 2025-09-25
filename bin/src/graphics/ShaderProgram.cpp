#include "headers/graphics/ShaderProgram.hpp"
#include "spdlog/spdlog.h"
#include <GLFW/glfw3.h>  

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
{
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
}

void ShaderProgram::LinkShaderProgram()
{
    spdlog::info("Linking shader program");
    // We assume shaders are precompiled
    this->shaderProgramId = glCreateProgram();

    glAttachShader(shaderProgramId, this->vertexShader->GetShaderId());
    glAttachShader(shaderProgramId, this->fragmentShader->GetShaderId());

    glLinkProgram(shaderProgramId);

    GLint success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
        spdlog::critical("Failed to link shader program");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void ShaderProgram::UseShaderProgram()
{
    glUseProgram(this->shaderProgramId);
}