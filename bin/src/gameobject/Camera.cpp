#include "headers/gameobject/Camera.hpp"
#include "spdlog/spdlog.h"
#include "headers/interfaces/Observer.hpp" 
#include "headers/services/LightFactory.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "headers/graphics/Skybox.hpp"
#include "headers/core/Application.hpp"
#include "headers/services/GameObjectFactory.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/gamelogic/Scene.hpp"

Camera::Camera(Scene* scene) : forward(0.0f, 0.0f, -1.0f), eye(0.0f, 2.0f, 2.0f), up(0.0f, 1.0f, 0.0f), speed(25.0f), scene(scene)
{
    forward = glm::normalize(forward);
    pitch = 90.0f;
    yaw = -90.0f;

}

void Camera::Init()
{
    Transform* flashlightTransform = new Transform();
    flashlightTransform->SetLocalPosition(eye);

    flashLight = scene->lightFactory.GetSpotLight(
        flashlightTransform,
        glm::vec3(1.0f, 1.0f, 1.0f),
        5.0f,
        0.09f,
        0.032f,
        -forward,
        15.0f,
        17.0f
    );
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
    return glm::perspective(glm::radians(this->fov), this->width / this->height, 0.1f, 10000.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(eye, eye + forward, up);
}

void Camera::ResizeViewport(GLFWwindow* window)
{
    int width;
    int height;

    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

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
        yoffset *= -sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(pitch > 179.0f) pitch = 179.0f;
        if(pitch < 1.0f) pitch = 1.0f;

        glm::vec3 dir;
        dir.x = sin(glm::radians(pitch)) * cos(glm::radians(yaw));
        dir.y = cos(glm::radians(pitch));
        dir.z = sin(glm::radians(pitch)) * sin(glm::radians(yaw));
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

            //appContext->scene->DeleteGameObject(id);

            auto newTree = appContext->scene->gameObjectFactory.GetGameObject(
                    "newTree",
                    MeshFactory::GetInstance().LoadTree(),
                    new Transform()
                );
            newTree->transform->SetLocalPosition(pos);
            newTree->transform->SetLocalScale(glm::vec3(0.1f));
            appContext->scene->AddGameObject(newTree);

            points.push_back(pos);

        }
        leftButtonPressed = true;
    }
    else
    {
        leftButtonPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        bezier = std::make_shared<BezierSplineTransform>(points, 0.2f);
        points.clear();

        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        AppContext* appContext = app->GetAppContext();

        auto car = appContext->scene->FindGameObjectByName("Car");
        if(car)
        {
            car->transform->AddBasicTransform(bezier);
        }
        
        bezier = nullptr;
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

glm::vec3 Camera::GetPosition()
{
    return eye;
}

