#include "headers/graphics/TextSimpleMesh.hpp"
#include <iostream>
#include "headers/pch.hpp"


TextSimpleMesh::TextSimpleMesh(vector<glm::vec3> vertices, vector<glm::vec3> normal, vector<glm::vec2> uv, std::shared_ptr<Material> material)
    : material(material)
{
    int count = std::min(vertices.size(), normal.size());
    this->vertexCount = vertices.size();
    for (int i = 0; i < count; i++) 
    {
        this->vertices.push_back(TextVertex{vertices[i], normal[i], uv[i]});
    }

    glGenBuffers(1, &this->VBO);
    glGenVertexArrays(1, &this->VAO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(TextVertex), this->vertices.data(), GL_STATIC_DRAW);

    // Position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)offsetof(TextVertex, normal));
    glEnableVertexAttribArray(1);

    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)offsetof(TextVertex, uv));
    glEnableVertexAttribArray(2);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void TextSimpleMesh::Render(glm::mat4 transformMatrix)
{   
    this->material->Use();
    this->material->SetTransformMatrix(transformMatrix);
    // Bind VAO
    glBindVertexArray(this->VAO);
    // Render vertices
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
    
    glBindVertexArray(0);
}

Material* TextSimpleMesh::GetMaterial()
{
    return material.get();
}