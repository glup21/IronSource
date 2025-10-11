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

    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;


    float speed;

    void NotifyAll() override;
public:
    Camera();
    ~Camera() = default;

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();

    // Only update if input from keyboard or mouse is present
    void Update();
    void ProcessInput(GLFWwindow* window, float deltaTime);
};