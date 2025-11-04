#include "headers/graphics/Model.hpp"

void Model::Render(glm::mat4 transformMatrix)
{
    for(const auto& mesh : meshes)
    {
        mesh->Render(transformMatrix);
    }
}

void Model::AddMesh(const std::shared_ptr<Mesh>& mesh)
{
    this->meshes.push_back(mesh);
}