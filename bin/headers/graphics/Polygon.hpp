#pragma once

#include "headers/interfaces/IRenderTarget.hpp"
#include <vector>
#include <glm/vec3.hpp> 
using std::vector;

struct VertexColor
{
    glm::vec3 vertex;
    glm::vec3 color;
};

// Deprecated class, which has its points hardocoded
// Learning purposes only
class Polygon : public IRenderTarget
{
public:

    Polygon(vector<glm::vec3> vertices, vector<glm::vec3> color);
    ~Polygon() = default;

    vector<VertexColor> vertices;
    void Render();

};