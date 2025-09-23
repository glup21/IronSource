#include "headers/graphics/Polygon.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

Polygon::Polygon(vector<glm::vec3> vertices, vector<glm::vec3> color)
{
    int count = std::min(vertices.size(), color.size());

    for (int i = 0; i < count; i++) 
    {
        this->vertices.push_back(VertexColor{vertices[i], color[i]});
    }

}

void Polygon::Render()
{
    // DEPRECATED, REMOVE LATER
    glBegin(GL_TRIANGLES);
    for( VertexColor v : vertices )
    {
        glColor3f(v.color.x, v.color.y, v.color.z);
        glVertex3f(v.vertex.x, v.vertex.y, v.vertex.z);
    }
    glEnd();
}

// Its a bit strange to pass path to shaders separately in Init method, but I dont want to see it in any IRenderTarget
// children. So I need to create RenderTargetFactory or something, which will take input from json and init everything
void Polygon::Init(ShaderLibrary* shaderLibrary, std::string vertexShader, std::string fragmentShader)
{
    this->shaderProgram = shaderLibrary->GetShaderProgram(vertexShader, fragmentShader);

    glGenBuffers(1, &this->VBO);
    glGenVertexArrays(1, &this->VAO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexColor), this->vertices.data(), GL_STATIC_DRAW);

    // Position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)0);
    glEnableVertexAttribArray(0);

    // Color 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)offsetof(VertexColor, color));
    glEnableVertexAttribArray(1);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}