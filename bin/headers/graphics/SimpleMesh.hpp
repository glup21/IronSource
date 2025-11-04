#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Material.hpp"
#include <vector>
#include <glm/vec3.hpp> 
#include <string>
#include <memory>

using std::vector;

struct SimpleVertex
{
    glm::vec3 vertex;
    glm::vec3 color;
    glm::vec3 normal;
};

// Simplified version of Mesh, which uses color directly, omitting textures 
class SimpleMesh : public IRenderTarget
{
public:
    SimpleMesh(vector<glm::vec3> vertices, vector<glm::vec3> color, vector<glm::vec3> normal, std::shared_ptr<Material> material);
    SimpleMesh() = default;
    ~SimpleMesh() = default;

    void Render(glm::mat4 transformMatrix);

private:
    vector<SimpleVertex> vertices;
    std::shared_ptr<Material> material;
    GLuint VBO, VAO;
    size_t vertexCount;
};