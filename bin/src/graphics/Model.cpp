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

Mesh* Model::GetMesh(int index)
{
    if(index < 0 || index >= meshes.size() || meshes.size() == 0)
        return nullptr;

    return meshes.at(index).get();
}