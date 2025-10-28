#pragma once
#include "headers/graphics/Shader.hpp"
#include "headers/interfaces/Observer.hpp"
#include "headers/gameobject/Camera.hpp"
#include "headers/graphics/PointLight.hpp"
#include "headers/graphics/AmbientLight.hpp"
#include "headers/graphics/DirectionalLight.hpp"
#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>

class ShaderProgram : public Observer
{
private:
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> fragmentShader;

    GLuint shaderProgramId;
    int lightCount;

    void HandlePointLight(PointLight* pointLight);
    void HandleAmbientLight(AmbientLight* ambientLight);
    void HandleDirectionalLight(DirectionalLight* directionalLight);

public:
    ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

    void LinkShaderProgram();
    void UseShaderProgram();

    void SetUniform(std::string name, glm::mat4 matrix4);
    void SetUniform(std::string name, glm::vec3 vec);
    void SetUniform(std::string name, float value);

    void Update(Subject* caller) override;
    void Reset();
};