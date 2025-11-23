#include "headers/gameobject/Camera.hpp"
#include "spdlog/spdlog.h"
#include "headers/interfaces/Observer.hpp" 
#include "headers/services/LightFactory.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "headers/graphics/Skybox.hpp"
#include "headers/core/Application.hpp"
#include "headers/services/GameObjectFactory.hpp"
#include "headers/services/MeshFactory.hpp"

Camera::Camera() : forward(0.0f, 0.0f, -1.0f), eye(0.0f, 2.0f, 2.0f), up(0.0f, 1.0f, 0.0f), speed(10.0f)
{
    forward = glm::normalize(forward);
    Transform* flashlightTransform = new Transform();
    flashlightTransform->SetLocalPosition(eye);
    flashLight = std::shared_ptr<SpotLight>(LightFactory::GetInstance().GetSpotLight(
        flashlightTransform,
        glm::vec3(1.0f, 1.0f, 1.0f),
        5.0f,
        0.09f,
        0.032f,
        -forward,
        15.0f,
        17.0f
    ));
    flashLight->SetEnabled(false);
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
    return glm::perspective(glm::radians(this->fov), this->width / this->height, 0.1f, 200.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(eye, eye + forward, up);
}

void Camera::ResizeViewport(int width, int height)
{
    this->width = (float)width;
    this->height = (float)height;
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime)
{
    static bool fPressedLastFrame = false;

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

    bool fPressedNow = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
    if (fPressedNow && !fPressedLastFrame)
        this->flashLight->SetEnabled(!this->flashLight->IsEnabled());
    fPressedLastFrame = fPressedNow;

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
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if(!leftButtonPressed)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            int id;
            // Reads from frame buffer 
            glReadPixels(xpos, height - static_cast<int>(ypos), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &id);
            spdlog::info("X: {}; Y: {}", xpos, height - static_cast<int>(ypos));
            spdlog::info("GameObject ID: {}", id);

            float depth;
            glReadPixels(xpos, height - static_cast<int>(ypos), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glm::vec4 viewPort = glm::vec4(0, 0, width, height);
            glm::vec3 point = glm::vec3( xpos, static_cast<double>(height) - ypos, depth);
            glm::vec3 pos = glm::unProject(point, GetViewMatrix(), GetProjectionMatrix(), viewPort);

            spdlog::info("Width: {}; Height: {}", width, height);
            spdlog::info("X: {}; Y: {}; Z: {}", pos.x, pos.y, pos.z);

            Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
            AppContext* appContext = app->GetAppContext();

            // auto newTree = GameObjectFactory::GetInstance().GetGameObject(
            //         "newTree",
            //         MeshFactory::GetInstance().LoadTree(),
            //         new Transform()
            //     );
            // newTree->transform->SetLocalPosition(pos);
            // appContext->scene->AddGameObject(newTree);

            appContext->scene->DeleteGameObject(id);
        }
        leftButtonPressed = true;
    }
    else
    {
        leftButtonPressed = false;
    }

    this->flashLight->SetDirection(forward);
    this->flashLight->transform->SetLocalPosition(eye);
    Update();
}


void Camera::Update()
{
    NotifyAll();
    this->flashLight->Update();
}

void Camera::SetSkybox(Skybox* skybox)
{
    this->skybox = std::unique_ptr<Skybox>(skybox);
}

void Camera::RenderSkybox()
{
    this->skybox->Render(
        GetProjectionMatrix(),
        glm::mat4(glm::mat3(GetViewMatrix()))
    );
}
