#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "headers/interfaces/Subject.hpp"

class Camera : public Subject
{
private:
    glm::vec3 forward;
    glm::vec3 eye;
    glm::vec3 up;

    float fov = 135.0f;
    float width = 800.0f;
    float height = 600.0f;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;
    bool rotating = false;

    float speed;

    void NotifyAll() override;
public:
    Camera();
    ~Camera() = default;

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    
    void Update();
    void ProcessInput(GLFWwindow* window, float deltaTime);
    void ResizeViewport(int width, int height);
};