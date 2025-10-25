#include "headers/graphics/ShaderProgram.hpp"
#include "headers/gameobject/Camera.hpp"
#include "headers/graphics/PointLight.hpp"
#include "spdlog/spdlog.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


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
    glUseProgram(this->shaderProgramId);

    GLint uniformLoc = glGetUniformLocation(shaderProgramId, name.c_str());
    if (uniformLoc < 0)
    {
        spdlog::critical("Failed to find uniform (mat4) in shader program: {}", name);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &matrix4[0][0]);
    //spdlog::debug("Set uniform (mat4): {}\n{}", name, glm::to_string(matrix4));
}

void ShaderProgram::SetUniform(std::string name, glm::vec3 vec)
{
    glUseProgram(this->shaderProgramId);

    GLint uniformLoc = glGetUniformLocation(this->shaderProgramId, name.c_str());
    if (uniformLoc < 0)
    {
        // DEBUG
        // spdlog::critical("Failed to find uniform (vec3) in shader program: {}", name);
        // glfwTerminate();
        // exit(EXIT_FAILURE);
    }

    glUniform3fv(uniformLoc, 1, &vec[0]);
    //spdlog::debug("Set uniform (vec3): {} = {}", name, glm::to_string(vec));
}

void ShaderProgram::SetUniform(std::string name, float value)
{
    glUseProgram(this->shaderProgramId);

    GLint uniformLoc = glGetUniformLocation(this->shaderProgramId, name.c_str());
    if (uniformLoc < 0)
    {
        // DEBUG
        // spdlog::critical("Failed to find uniform (float) in shader program: {}", name);
        // glfwTerminate();
        // exit(EXIT_FAILURE);
        return;
    }

    glUniform1f(uniformLoc, value);
    // spdlog::debug("Set uniform (float): {} = {}", name, value);
}


void ShaderProgram::Update(Subject* caller)
{
    Camera* camera = dynamic_cast<Camera*>(caller);
    if (camera) 
    {
        // We dont need to recalculate product of projection and view matrix on each thread
        glm::mat4 cameraMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
        SetUniform("cameraMatrix", cameraMatrix);
    }

    PointLight* pointLight = dynamic_cast<PointLight*>(caller);
    if (pointLight)
    {
        SetUniform("lights[" + std::to_string(lightCount) + "].position", pointLight->GetPosition());
        SetUniform("lights[" + std::to_string(lightCount) + "].color", pointLight->GetColor());
        SetUniform("lights[" + std::to_string(lightCount) + "].k_l", pointLight->GetLinear());
        SetUniform("lights[" + std::to_string(lightCount) + "].k_q", pointLight->GetQuadratic());
        lightCount++;
    }

}

void ShaderProgram::Reset()
{
    lightCount = 0;
}