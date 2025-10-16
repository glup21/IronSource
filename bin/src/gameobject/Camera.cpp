#include "headers/gameobject/Camera.hpp"
#include "spdlog/spdlog.h"
#include "headers/interfaces/Observer.hpp" 
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : forward(0.0f, 0.0f, -1.0f), eye(0.0f, 0.0f, 2.0f), up(0.0f, 1.0f, 0.0f), speed(10.0f)
{
    forward = glm::normalize(forward);
}

void Camera::NotifyAll() 
{
    for(auto* observer : observers)
    {
        observer->Update(this);
    }
}

glm::mat4 Camera::GetProjectionMatrix()
{
    // Default constants, replace with variables later
    return glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(eye, eye + forward, up);
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime)
{
    glm::vec3 right = glm::normalize(glm::cross(forward, up));
    float velocity = speed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        eye += forward * velocity;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        eye -= forward * velocity;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        eye -= right * velocity;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        eye += right * velocity;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (!rotating)
        {
            lastX = xpos;
            lastY = ypos;
            rotating = true;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;

        glm::vec3 dir;
        dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        dir.y = sin(glm::radians(pitch));
        dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward = glm::normalize(dir);
    }
    else
    {
        rotating = false;
    }

    Update();
}

void Camera::Update()
{
    NotifyAll();
}
