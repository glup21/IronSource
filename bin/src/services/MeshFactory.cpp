#define TINYOBJLOADER_IMPLEMENTATION
#include "headers/services/MeshFactory.hpp"
#include "headers/services/GlobalConfig.hpp"
#include <tiny_obj_loader.h>
#include <spdlog/spdlog.h>
#include "headers/services/MaterialFactory.hpp"


/*    static std::vector<std::shared_ptr<SimpleMesh>> LoadAllPredefinedModels();
    static std::shared_ptr<SimpleMesh> LoadSphere(std::string vertexShaderPath = "", std::string fragmentShaderPath = "");
    static std::shared_ptr<Mesh> LoadFromFile(std::string fileName);*/
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
    std::string vertexShader = vertexShaderPath.empty() 
        ? GlobalConfig::GetDefaultVertexShaderPath() 
        : vertexShaderPath;
    std::string fragmentShader = fragmentShaderPath.empty() 
        ? GlobalConfig::GetDefaultFragmentShaderPath() 
        : fragmentShaderPath;
    auto mesh = std::make_shared<SimpleMesh>(positions, colors, colors, MaterialFactory::GetMaterial(vertexShaderPath, fragmentShaderPath));
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

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, MaterialFactory::GetMaterial()));
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

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, MaterialFactory::GetMaterial()));
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

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, MaterialFactory::GetMaterial()));
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

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, MaterialFactory::GetMaterial()));
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

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, MaterialFactory::GetMaterial()));
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

    meshes.push_back(std::make_shared<SimpleMesh>(positions, colors, normals, MaterialFactory::GetMaterial()));
    positions.clear();
    colors.clear();
    normals.clear();

    return meshes;
}

std::shared_ptr<Mesh> MeshFactory::LoadFromFile(std::string filePath)
{
    spdlog::info("Loading OBJ model from path: {}", filePath);

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warningMessage, errorMessage;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warningMessage,
        &errorMessage,
        filePath.c_str(),
        nullptr, 
        true     
    );

    if (!warningMessage.empty())
        spdlog::warn("TinyObjLoader warning: {}", warningMessage);

    if (!errorMessage.empty())
        spdlog::error("TinyObjLoader error: {}", errorMessage);

    if (!success)
    {
        spdlog::critical("Failed to load OBJ file: {}", filePath);
        return nullptr;
    }

    spdlog::info("OBJ loaded successfully. Found {} vertices, {} shapes, {} materials.",
        attributes.vertices.size() / 3,
        shapes.size(),
        materials.size()
    );

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;

    for (auto shape : shapes)
    {
        spdlog::debug("Processing shape: {}", shape.name);

        for (const auto& index : shape.mesh.indices)
        {
            glm::vec3 position(0.0f);
            glm::vec3 normal(0.0f);
            //glm::vec2 texCoord(0.0f);

            if (index.vertex_index >= 0)
            {
                position = glm::vec3(
                    attributes.vertices[3 * index.vertex_index + 0],
                    attributes.vertices[3 * index.vertex_index + 1],
                    attributes.vertices[3 * index.vertex_index + 2]
                );
                positions.push_back(position);
            }
            
            if (index.normal_index >= 0)
            {
                normal = glm::vec3(
                    attributes.normals[3 * index.normal_index + 0],
                    attributes.normals[3 * index.normal_index + 1],
                    attributes.normals[3 * index.normal_index + 2]
                );
                normals.push_back(normal);
            }

            // if (index.texcoord_index >= 0)
            // {
            //     texCoord = glm::vec2(
            //         attributes.texcoords[2 * index.texcoord_index + 0],
            //         attributes.texcoords[2 * index.texcoord_index + 1]
            //     );
            // }

            // Place texture coordinate here later
            //mesh->AddVertex(position, normal, glm::vec3(1.0));
        }
    }

    auto mesh = std::make_shared<Mesh>(positions, normals, normals, MaterialFactory::GetMaterial());
    spdlog::info("Finished processing OBJ mesh: {}", filePath);
    return mesh;
}