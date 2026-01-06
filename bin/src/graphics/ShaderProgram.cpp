#include "headers/graphics/ShaderProgram.hpp"
#include "spdlog/spdlog.h"
#include "headers/gameobject/Camera.hpp"
#include "headers/graphics/PointLight.hpp"
#include "headers/graphics/AmbientLight.hpp"
#include "headers/graphics/DirectionalLight.hpp"
#include "headers/graphics/SpotLight.hpp"
#include "headers/services/LightFactory.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
{
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
}

void ShaderProgram::Link()
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
    SetUniform("w", 500.0f);
    
}

void ShaderProgram::Use()
{
    glUseProgram(this->shaderProgramId);
}

void ShaderProgram::SetUniform(std::string name, glm::mat4 matrix4)
{
    glUseProgram(this->shaderProgramId);

    GLint uniformLoc = glGetUniformLocation(shaderProgramId, name.c_str());
    if (uniformLoc < 0)
    {
        // spdlog::critical("Failed to find uniform (mat4) in shader program: {}", name);
        // glfwTerminate();
        // exit(EXIT_FAILURE);
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
        //DEBUG
        // spdlog::critical("Failed to find uniform (float) in shader program: {}", name);
        // glfwTerminate();
        // exit(EXIT_FAILURE);
        return;
    }

    glUniform1f(uniformLoc, value);
    // spdlog::debug("Set uniform (float): {} = {}", name, value);
}

void ShaderProgram::SetUniform(std::string name, int value)
{
    glUseProgram(this->shaderProgramId);

    GLint uniformLoc = glGetUniformLocation(this->shaderProgramId, name.c_str());
    if (uniformLoc < 0)
    {
        //DEBUG
        // spdlog::critical("Failed to find uniform (float) in shader program: {}", name);
        // glfwTerminate();
        // exit(EXIT_FAILURE);
        return;
    }

    glUniform1i(uniformLoc, value);
    // spdlog::debug("Set uniform (float): {} = {}", name, value);
}

void ShaderProgram::SetUniform(std::string name, bool value)
{
    glUseProgram(this->shaderProgramId);

    GLint uniformLoc = glGetUniformLocation(this->shaderProgramId, name.c_str());
    if (uniformLoc < 0)
    {
        //DEBUG
        // spdlog::critical("Failed to find uniform (float) in shader program: {}", name);
        // glfwTerminate();
        // exit(EXIT_FAILURE);
        return;
    }

    glUniform1i(uniformLoc, value);
    // spdlog::debug("Set uniform (float): {} = {}", name, value);
}

void ShaderProgram::Update(Subject* caller)
{
    Camera* camera = dynamic_cast<Camera*>(caller);
    if (camera) 
    {
        SetUniform("viewMatrix", camera->GetViewMatrix());
        SetUniform("projectionMatrix", camera->GetProjectionMatrix());
        SetUniform("viewPos", camera->GetPosition());
    }
    if(auto* light = dynamic_cast<Light*>(caller))
    {
        switch (light->GetType())
        {
            case LightType::Point:
                HandlePointLight(static_cast<PointLight*>(light));
                break;
            case LightType::Ambient:
                HandleAmbientLight(static_cast<AmbientLight*>(light));
                break;
            case LightType::Directional:
                HandleDirectionalLight(static_cast<DirectionalLight*>(light));
                break;
            case LightType::Spot:
                HandleSpotLight(static_cast<SpotLight*>(light));
                break;
            default:
                break;
        }
    }
}

void ShaderProgram::HandlePointLight(PointLight* pointLight)
{
    SetUniform("pointLights[" + std::to_string(pointLightCount) + "].color", pointLight->GetColor());
    SetUniform("pointLights[" + std::to_string(pointLightCount) + "].intensity", pointLight->GetIntensity());

    SetUniform("pointLights[" + std::to_string(pointLightCount) + "].position", pointLight->GetPosition());
    
    SetUniform("pointLights[" + std::to_string(pointLightCount) + "].k_l", pointLight->GetLinear());
    SetUniform("pointLights[" + std::to_string(pointLightCount) + "].k_q", pointLight->GetQuadratic());

    pointLightCount++;  
}

void ShaderProgram::HandleAmbientLight(AmbientLight* ambientLight)
{
    SetUniform("ambientLights[" + std::to_string(ambientLightCount) + "].color", ambientLight->GetColor());
    SetUniform("ambientLights[" + std::to_string(ambientLightCount) + "].intensity", ambientLight->GetIntensity());
    ambientLightCount++;  
}

void ShaderProgram::HandleDirectionalLight(DirectionalLight* directionalLight)
{
    SetUniform("directionalLights[" + std::to_string(directionalLightCount) + "].color", directionalLight->GetColor());
    SetUniform("directionalLights[" + std::to_string(directionalLightCount) + "].intensity", directionalLight->GetIntensity());
    SetUniform("directionalLights[" + std::to_string(directionalLightCount) + "].direction", directionalLight->GetDirection());
    directionalLightCount++;  
}

void ShaderProgram::HandleSpotLight(SpotLight* spotLight)
{
    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].enabled", spotLight->IsEnabled());
    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].position", spotLight->transform->GetLocalPosition());
    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].direction", spotLight->GetDirection());

    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].color", spotLight->GetColor());

    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].intensity", spotLight->GetIntensity());
    
    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].k_l", spotLight->GetLinear());
    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].k_q", spotLight->GetQuadratic());

    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].cutOff", (float)cos(glm::radians(spotLight->GetCutOff())));
    SetUniform("spotLights[" + std::to_string(spotLightCount) + "].outerCutOff", (float)cos(glm::radians(spotLight->GetOuterCutOff())));

    Texture* lightTexture = spotLight->GetLightTexture();
    if(lightTexture)
    {
        lightTexture->Use(GL_TEXTURE0 + 9); // Lets put max count of color+normal textures at 8
        SetUniform("pointLights[" + std::to_string(spotLightCount) + "].lightTexture", 9);
    }

    spotLightCount++;  
}

void ShaderProgram::Reset()
{
    ambientLightCount = pointLightCount = directionalLightCount = spotLightCount = 0;
}

void ShaderProgram::SendLightCounts() 
{
    auto lightFactory = LightFactory::GetInstance();
    SetUniform("numAmbientLights", lightFactory.ambientLightCount);
    SetUniform("numPointLights", lightFactory.pointLightCount);
    SetUniform("numDirectionalLights", lightFactory.directionalLightCount);
    SetUniform("numSpotLights", lightFactory.spotLightCount);
}