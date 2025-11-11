#include "headers/graphics/Skybox.hpp"
#include "headers/services/MeshFactory.hpp"
#include "headers/services/MaterialFactory.hpp"
#include "headers/services/TextureFactory.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include "spdlog/spdlog.h"
#include "lib/stb_image/stb_image.h" 

Skybox::Skybox(std::vector<glm::vec3> vertices, std::vector<std::string> faces, std::shared_ptr<ShaderProgram> shaderProgram)
    : vertices(vertices), shaderProgram(shaderProgram), vertexCount(vertices.size())
{
    InitMesh();
    InitCubemap(faces);
}

void Skybox::InitCubemap(std::vector<std::string> faces)
{
    glGenTextures(1, &cubemapTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureID);

    if(faces.size() != 6)
    {
        spdlog::critical("Wrong face count! Aborting");
        exit;
    }

    for( int i = 0; i < 6; i++)
    {
        int width, height, channels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);

        if (data) 
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::InitMesh()
{
    glGenBuffers(1, &this->VBO);
    glGenVertexArrays(1, &this->VAO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

    // Position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Skybox::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    this->shaderProgram->Use();
    this->shaderProgram->SetUniform("projectionMatrix", projectionMatrix);
    this->shaderProgram->SetUniform("viewMatrix", viewMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureID);
    shaderProgram->SetUniform("skyboxCubemap", 0); 

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));

    glBindVertexArray(0);
}

void Skybox::Render(glm::mat4 transformMatrix)
{
    // Just to make compiler shut up
}