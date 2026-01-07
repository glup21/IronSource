#include "headers/services/MeshFactory.hpp"
#include "headers/services/GlobalConfig.hpp"
#include <spdlog/spdlog.h>
#include "headers/services/MaterialFactory.hpp"
#include "Models/skybox.h"
#include <filesystem>

MeshFactory::MeshFactory(MaterialFactory* materialFactory, ShaderLibrary* shaderLibrary) : 
    materialFactory(materialFactory), shaderLibrary(shaderLibrary)
{

}

std::shared_ptr<SimpleMesh> MeshFactory::LoadSphere(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;

    positions.reserve(17280 / 6);
    colors.reserve(17280 / 6);

    for (size_t i = 0; i < 17280; i += 6)
    {
        positions.emplace_back(sphere[i], sphere[i + 1], sphere[i + 2]);
        colors.emplace_back(sphere[i + 3], sphere[i + 4], sphere[i + 5]);
    }

    auto mesh = std::make_shared<SimpleMesh>(positions, colors, colors, materialFactory->GetMaterial(vertexShaderPath, fragmentShaderPath));
    return mesh;
}

std::shared_ptr<SimpleMesh> MeshFactory::LoadTree()
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;

    int vertexCount = 92814 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(tree[i], tree[i + 1], tree[i + 2]);
        colors.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
        normals.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
    }

    auto mesh = std::make_shared<SimpleMesh>(positions, colors, colors, materialFactory->GetMaterial());
    return mesh;
}

std::vector<std::shared_ptr<SimpleMesh>> MeshFactory::LoadAllPredefinedModels()
{
    std::vector<std::shared_ptr<SimpleMesh>> meshes;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;

    // Bushes
    int vertexCount = 8730 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(bushes[i], bushes[i + 1], bushes[i + 2]);
        colors.emplace_back(bushes[i + 3], bushes[i + 4], bushes[i + 5]);
        normals.emplace_back(bushes[i + 3], bushes[i + 4], bushes[i + 5]);
    }

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, materialFactory->GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();
    // Gift
    vertexCount = 66624 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(gift[i], gift[i + 1], gift[i + 2]);
        colors.emplace_back(gift[i + 3], gift[i + 4], gift[i + 5]);
        normals.emplace_back(gift[i + 3], gift[i + 4], gift[i + 5]);
    }

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, materialFactory->GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();

    // Plain
    vertexCount = 36;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(plain[i], plain[i + 1], plain[i + 2]);
        colors.emplace_back(plain[i + 3], plain[i + 4], plain[i + 5]);
        normals.emplace_back(plain[i + 3], plain[i + 4], plain[i + 5]);
    }

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, materialFactory->GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();

    // Suzi flat
    vertexCount = 2904 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(suziFlat[i], suziFlat[i + 1], suziFlat[i + 2]);
        colors.emplace_back(suziFlat[i + 3], suziFlat[i + 4], suziFlat[i + 5]);
        normals.emplace_back(suziFlat[i + 3], suziFlat[i + 4], suziFlat[i + 5]);
    }

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, materialFactory->GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();

    // Suzi smooth
    vertexCount = 2904 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(suziSmooth[i], suziSmooth[i + 1], suziSmooth[i + 2]);
        colors.emplace_back(suziSmooth[i + 3], suziSmooth[i + 4], suziSmooth[i + 5]);
        normals.emplace_back(suziSmooth[i + 3], suziSmooth[i + 4], suziSmooth[i + 5]);
    }

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, materialFactory->GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();

    // Tree
    vertexCount = 92814 * 6;

    positions.reserve(vertexCount / 6);
    colors.reserve(vertexCount / 6);
    normals.reserve(vertexCount / 6);

    for (size_t i = 0; i < vertexCount; i += 6)
    {
        positions.emplace_back(tree[i], tree[i + 1], tree[i + 2]);
        colors.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
        normals.emplace_back(tree[i + 3], tree[i + 4], tree[i + 5]);
    }

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, materialFactory->GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();

    return meshes;
}

std::shared_ptr<Model> MeshFactory::LoadFromFile(std::string filePath, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    spdlog::info("Trying to find a model in cache");

    MeshKey key{filePath, vertexShaderPath, fragmentShaderPath};

    auto iterator = models.find(key);
    if(iterator != models.end())
    {
        spdlog::info("Found cached mesh!");
        return iterator->second;
    }

    spdlog::info("Failed to find mesh in cache");
    spdlog::info("Loading OBJ model from path: {}", filePath);

    tinyobj::ObjReaderConfig config;
    std::filesystem::path path(filePath);
    config.mtl_search_path = path.parent_path(); 
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filePath, config)) {
        spdlog::error("TinyObjReader failed: {}", reader.Error());
        return nullptr;
    }

    if (!reader.Warning().empty())
        spdlog::warn("TinyObjLoader warning: {}", reader.Warning());

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();
    const auto& materials = reader.GetMaterials();

    spdlog::info("OBJ loaded: {} vertices, {} shapes, {} materials",
        attrib.vertices.size() / 3,
        shapes.size(),
        materials.size()
    );

    std::shared_ptr<Model> model = std::make_shared<Model>();

    for (const auto& shape : shapes)
    {
        spdlog::debug("Processing shape: {}", shape.name);

        // Map material to list of vertices
        std::map<int, std::vector<Vertex>> materialToVertices;

        size_t faceOffset = 0;
        for (size_t faceIndex = 0; faceIndex < shape.mesh.num_face_vertices.size(); faceIndex++)
        {
            int faceVertexCount = shape.mesh.num_face_vertices[faceIndex];
            int matId = shape.mesh.material_ids[faceIndex];

            for (size_t vertexIndex = 0; vertexIndex < faceVertexCount; vertexIndex++)
            {
                tinyobj::index_t idx = shape.mesh.indices[faceOffset + vertexIndex];
                Vertex vertex;

                // Position
                vertex.vertex = glm::vec3(
                    static_cast<float>(attrib.vertices[3 * idx.vertex_index + 0]),
                    static_cast<float>(attrib.vertices[3 * idx.vertex_index + 1]),
                    static_cast<float>(attrib.vertices[3 * idx.vertex_index + 2])
                );

                // Normal
                if (idx.normal_index >= 0)
                    vertex.normal = glm::vec3(
                        static_cast<float>(attrib.normals[3 * idx.normal_index + 0]),
                        static_cast<float>(attrib.normals[3 * idx.normal_index + 1]),
                        static_cast<float>(attrib.normals[3 * idx.normal_index + 2])
                    );
                else
                    vertex.normal = glm::vec3(0.0f);

                // TexCoord
                if (idx.texcoord_index >= 0)
                    vertex.texCoord = glm::vec2(
                        static_cast<float>(attrib.texcoords[2 * idx.texcoord_index + 0]),
                        1.0f - static_cast<float>(attrib.texcoords[2 * idx.texcoord_index + 1])
                    );
                else
                    vertex.texCoord = glm::vec2(0.0f);

                materialToVertices[matId].push_back(vertex);
            }

            faceOffset += faceVertexCount;
        }

        for (auto& pair : materialToVertices)
        {
            int matId = pair.first;
            std::vector<Vertex> vertices = pair.second;

            std::shared_ptr<Material> mat = materialFactory->GetMaterialFromMtl(materials[matId], path.parent_path(), vertexShaderPath, fragmentShaderPath);
            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, mat);
            model->AddMesh(mesh);
        }
    }

    spdlog::info("Finished processing OBJ file: {}", filePath);
    models[key] = model;
    
    return model;
}

Skybox* MeshFactory::GetSkybox()
{
    std::vector<glm::vec3> positions;
    positions.reserve(sizeof(skybox) / sizeof(float) / 3);
    for (size_t i = 0; i < sizeof(skybox) / sizeof(float); i += 3)
    {
        positions.emplace_back(skybox[i], skybox[i + 1], skybox[i + 2]);
    }

    auto skybox = new Skybox(positions, GlobalConfig::GetDefaultSkyboxFaces(), shaderLibrary->GetShaderProgram(
        GlobalConfig::GetDefaultSkyboxVertexShaderPath(),
        GlobalConfig::GetDefaultSkyboxFragmentShaderPath()
    ));

    return skybox;
}