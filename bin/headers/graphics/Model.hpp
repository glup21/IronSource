#pragma once
#include "headers/graphics/Mesh.hpp"

// Package for multiple Meshes
class Model : public IRenderTarget
{
private:
    std::vector<std::shared_ptr<Mesh>> meshes;
public: 
    Model() = default;
    Model(std::vector<std::shared_ptr<Mesh>> meshes);
    ~Model() = default;

    void Render(glm::mat4 transformMatrix);
    void AddMesh(const std::shared_ptr<Mesh>& mesh);
};