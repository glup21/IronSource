#pragma once
#include "headers/graphics/SpotLight.hpp"
#include "headers/interfaces/Subject.hpp"
#include "headers/transform/BezierSplineTransform.hpp"
#include "headers/pch.hpp"

class Skybox;
class Camera : public Subject
{
private:
    glm::vec3 forward;
    glm::vec3 eye;
    glm::vec3 up;

    float fov = 60.0f;
    float width = 800.0f;
    float height = 600.0f;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;
    bool rotating = false;
    bool leftButtonPressed = false;

    float speed;

    std::unique_ptr<SpotLight> flashLight;
    std::unique_ptr<Skybox> skybox;

    std::vector<glm::vec3> points;
    std::shared_ptr<BezierSplineTransform> bezier;

    void NotifyAll() override;
public:
    Camera();
    ~Camera() = default;

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    
    void Update();
    void ProcessInput(GLFWwindow* window, float deltaTime);
    void ResizeViewport(GLFWwindow* window);
    void SetSkybox(Skybox* skybox);
    void RenderSkybox();
};