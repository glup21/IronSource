#include "headers/graphics/Polygon.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

Polygon::Polygon(vector<glm::vec3> vertices, vector<glm::vec3> color)
{
    int count = std::min(vertices.size(), color.size());

    for (int i = 0; i < count; i++) {
        this->vertices.emplace_back(VertexColor{vertices[i], color[i]});
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