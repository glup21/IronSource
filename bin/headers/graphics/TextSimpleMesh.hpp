#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Material.hpp"
#include <vector>
#include <glm/vec3.hpp> 
#include <string>
#include <memory>

using std::vector;

struct TextVertex
{
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 uv;
};

// Simplified version of Mesh, which uses color directly, omitting textures 
class TextSimpleMesh : public IRenderTarget
{
public:
    TextSimpleMesh(vector<glm::vec3> vertices, vector<glm::vec3> normal, vector<glm::vec2> uv, std::shared_ptr<Material> material);
    TextSimpleMesh() = default;
    ~TextSimpleMesh() = default;

    void Render(glm::mat4 transformMatrix);
    Material* GetMaterial();
    
private:
    vector<TextVertex> vertices;
    std::shared_ptr<Material> material;
    GLuint VBO, VAO;
    size_t vertexCount;
};