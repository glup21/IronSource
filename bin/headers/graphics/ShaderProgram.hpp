#pragma once
#include "headers/graphics/Shader.hpp"
#include "headers/interfaces/Observer.hpp"
#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>

class Camera;
class PointLight;
class AmbientLight;
class DirectionalLight;
class SpotLight;

class ShaderProgram : public Observer
{
private:
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> fragmentShader;

    GLuint shaderProgramId;
    int pointLightCount = 0;
    int ambientLightCount = 0;
    int directionalLightCount = 0;
    int spotLightCount = 0;

    void HandlePointLight(PointLight* pointLight);
    void HandleAmbientLight(AmbientLight* ambientLight);
    void HandleDirectionalLight(DirectionalLight* directionalLight);
    void HandleSpotLight(SpotLight* spotLight);

public:
    ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

    void Link();
    void Use();

    void SetUniform(std::string name, glm::mat4 matrix4);
    void SetUniform(std::string name, glm::vec3 vec);
    void SetUniform(std::string name, float value);
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, bool value);

    void Update(Subject* caller) override;
    void Reset();
    void SendLightCounts();
};