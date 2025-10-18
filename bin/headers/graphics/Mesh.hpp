#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include <vector>
#include <glm/vec3.hpp> 
#include <string>
#include <memory>

using std::vector;

struct VertexColor
{
    glm::vec3 vertex;
    glm::vec3 color;
};


// Deprecated class, which has its points hardocoded
// Learning purposes only
class Mesh : public IRenderTarget
{
public:
    Mesh(vector<glm::vec3> vertices, vector<glm::vec3> color);
    ~Mesh() = default;

    void Render(glm::mat4 transformMatrix);
    void Init(ShaderLibrary* shaderLibrary, std::string vertexShader, std::string fragmentShader);

private:
    vector<VertexColor> vertices;
    std::shared_ptr<ShaderProgram> shaderProgram;
    GLuint VBO, VAO;
    size_t vertexCount;
};