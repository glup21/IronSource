#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Material.hpp"
#include <vector>
#include <glm/vec3.hpp> 
#include <string>
#include <memory>

using std::vector;

struct Vertex
{
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Mesh : public IRenderTarget
{
public:
    Mesh(vector<glm::vec3> vertices, vector<glm::vec3> normal, vector<glm::vec2> texCoord, std::shared_ptr<Material> material);
    Mesh(vector<Vertex> vertices, std::shared_ptr<Material> material);
    Mesh() = default;
    ~Mesh() = default;

    void Render(glm::mat4 transformMatrix);
    Material* GetMaterial();

private:
    vector<Vertex> vertices;
    std::shared_ptr<Material> material;
    GLuint VBO, VAO;
    size_t vertexCount;

    void Init();
    
};