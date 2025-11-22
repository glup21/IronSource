#include "headers/graphics/Mesh.hpp"
#include <iostream>
#include "headers/pch.hpp"

Mesh::Mesh(vector<glm::vec3> vertices, vector<glm::vec3> normal, vector<glm::vec2> texCoord, std::shared_ptr<Material> material)
    : material(material)
{
    int count = std::min(vertices.size(), normal.size());
    count = std::min((size_t)count, texCoord.size());

    this->vertexCount = vertices.size();
    for (int i = 0; i < count; i++) 
    {
        this->vertices.push_back(Vertex{vertices[i], normal[i], texCoord[i]});
    }

    Init();
}

Mesh::Mesh(vector<Vertex> vertices, std::shared_ptr<Material> material)
    : vertices(vertices), material(material), vertexCount(vertices.size())
{
    Init();
}

void Mesh::Init()
{
    glGenBuffers(1, &this->VBO);
    glGenVertexArrays(1, &this->VAO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

    // Position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normals 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // TexCoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::Render(glm::mat4 transformMatrix)
{   
    this->material->Use();
    this->material->SetTransformMatrix(transformMatrix);
    // Bind VAO
    glBindVertexArray(this->VAO);
    // Render vertices
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
    
    glBindVertexArray(0);
}

Material* Mesh::GetMaterial()
{
    return material.get();
}
