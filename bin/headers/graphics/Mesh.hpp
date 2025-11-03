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
    glm::vec3 color;
    glm::vec3 normal;
};

// Rework so it could work not only with Material and Texture, but with raw colors as well
class Mesh : public IRenderTarget
{
public:
    Mesh(vector<glm::vec3> vertices, vector<glm::vec3> color, vector<glm::vec3> normal, std::shared_ptr<Material> material);
    Mesh() = default;
    ~Mesh() = default;

    void Render(glm::mat4 transformMatrix);
    // Why Init using separate function?
    // void Init(ShaderLibrary* shaderLibrary, std::string vertexShader, std::string fragmentShader);
    // void AddVertex(glm::vec3 vertex, glm::vec3 color, glm::vec3 normal);

private:
    vector<Vertex> vertices;
    //std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Material> material;
    GLuint VBO, VAO;
    size_t vertexCount;
};