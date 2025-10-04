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
        spdlog::critical("Failed to link shader program");\
        GLint logLength;
        glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, '\0');
        glGetProgramInfoLog(shaderProgramId, logLength, nullptr, infoLog.data());

        spdlog::critical(infoLog);

        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void ShaderProgram::UseShaderProgram()
{
    glUseProgram(this->shaderProgramId);
}

void ShaderProgram::SetUniform(std::string name, glm::mat4 matrix4)
{
    GLuint uniformLoc = glGetUniformLocation(shaderProgramId, name.c_str());
    if(uniformLoc < 0)
    {
        // Replace later with statis Application method
        spdlog::critical("Failed to find uniform in shader program: {}", name);

        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &matrix4[0][0]);
}