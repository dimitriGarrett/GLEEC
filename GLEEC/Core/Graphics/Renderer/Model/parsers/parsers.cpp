#include "Core/Graphics/Renderer/Model/GeometryManager.h"
#include "obj.h"
#include "mtl.h"

#include "Core/Graphics/TextureManager.h"
#include "Core/Graphics/BufferManager.h"
#include "Core/Graphics/GPUManager.h"
#include "Core/Graphics/InstanceManager.h"
#include "Core/Graphics/ShaderManager.h"

#include <array>
#include <fstream>
#include <unordered_map>
#include <algorithm>

namespace GLEEC::Graphics::parsers
{
    inline Material* findMaterial(Geometry& geometry, std::string_view name)
    {
        for (ColorMaterial& material : geometry.colorMaterials) 
        {
            if (material.name == name) return &material;
        }

        for (TextureMaterial& material : geometry.textureMaterials) 
        {
            if (material.name == name) return &material;
        }

        return nullptr;
    }

    inline Mesh* findMesh(Geometry& geometry, std::string_view name)
    {
        for (Mesh& mesh : geometry.meshes)
        {
            if (mesh.name == name) return &mesh;
        }

        return nullptr;
    }

    // account for backslashes
#if GLEEC_WINDOWS
    std::string objfp(std::string objfp, const std::string& mtl)
#else
    std::string objfp(const std::string& objfp, const std::string& mtl)
#endif

    {
#if GLEEC_WINDOWS
        for (size_t i = objfp.size() - 1; i >= 0; ++i)
        {
            if (objfp[i] == '\\')
            {
                objfp[i] = '/';

                break;
            }
        }
#endif
        return objfp.substr(0, objfp.find_last_of('/') + 1) + mtl;
    }

    inline math::fvec3 read_triple(std::string_view data)
    {
        math::fvec3 temp = {};
        sscanf_s(data.data(), "%f %f %f", &temp.x, &temp.y, &temp.z);
        return temp;
    }

    inline math::fvec2 read_double(std::string_view data)
    {
        math::fvec2 temp = {};
        sscanf_s(data.data(), "%f %f", &temp.x, &temp.y);
        return temp;
    }

    inline float read_single(std::string_view data)
    {
        float temp = {};
        sscanf_s(data.data(), "%f", &temp);
        return temp;
    }

    struct Storage
    {
        std::vector<math::fvec3> verts = {};
        std::vector<math::fvec2> uv = {};
        std::vector<math::fvec3> norm = {};

        std::vector<Vertex> meshVertices = {};
        std::vector<Index>  meshIndices = {};
    };

    void addFace(std::string_view data, Storage& storage)
    {
        size_t count = std::count(data.begin(), data.end(), '/');

        if (count == 8)
        {
            std::array<unsigned int, 12> indices = {};

            sscanf_s(data.data(), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                &indices[0],
                &indices[1],
                &indices[2],
                &indices[3],
                &indices[4],
                &indices[5],
                &indices[6],
                &indices[7],
                &indices[8],
                &indices[9],
                &indices[10],
                &indices[11]);

            // vbo
            storage.meshVertices.emplace_back(
                storage.verts[indices[0] - 1],
                storage.uv[   indices[1] - 1],
                storage.norm[ indices[2] - 1]);

            storage.meshVertices.emplace_back(
                storage.verts[indices[3] - 1],
                storage.uv[   indices[4] - 1],
                storage.norm[ indices[5] - 1]);

            storage.meshVertices.emplace_back(
                storage.verts[indices[6] - 1],
                storage.uv[   indices[7] - 1],
                storage.norm[ indices[8] - 1]);

            storage.meshVertices.emplace_back(
                storage.verts[indices[9] - 1],
                storage.uv[   indices[10] - 1],
                storage.norm[ indices[11] - 1]);

            // ebo
            Index start = storage.meshVertices.size();

            storage.meshIndices.emplace_back(start);
            storage.meshIndices.emplace_back(start + 1);
            storage.meshIndices.emplace_back(start + 2);
            storage.meshIndices.emplace_back(start + 2);
            storage.meshIndices.emplace_back(start + 3);
            storage.meshIndices.emplace_back(start);
        }

        else if (count == 6)
        {
            std::array<unsigned int, 9> indices = {};

            sscanf_s(data.data(), "%d/%d/%d %d/%d/%d %d/%d/%d",
                &indices[0],
                &indices[1],
                &indices[2],
                &indices[3],
                &indices[4],
                &indices[5],
                &indices[6],
                &indices[7],
                &indices[8]);

            // vbo
            storage.meshVertices.emplace_back(
                storage.verts[indices[0] - 1],
                storage.uv[   indices[1] - 1],
                storage.norm[ indices[2] - 1]);

            storage.meshVertices.emplace_back(
                storage.verts[indices[3] - 1],
                storage.uv[   indices[4] - 1],
                storage.norm[ indices[5] - 1]);

            storage.meshVertices.emplace_back(
                storage.verts[indices[6] - 1],
                storage.uv[   indices[7] - 1],
                storage.norm[ indices[8] - 1]);

            // ebo
            Index start = storage.meshVertices.size();

            storage.meshIndices.emplace_back(start);
            storage.meshIndices.emplace_back(start + 1);
            storage.meshIndices.emplace_back(start + 2);
        }

        else
        {
            LOG_WARNING("Unknown number of vertices: {} in face definition: {}!",
                count, data);
        }
    }

    Geometry obj(std::string_view filepath)
    {
        Geometry geometry = {};
        geometry.filepath = filepath;

        std::ifstream file(geometry.filepath);

        if (!file.is_open())
        {
            LOG_WARNING("Failed to parse obj file: {}", filepath); return {};
        }

        std::string line = "";
        std::string header = "";
        std::string data = "";

        Mesh* currentMesh = nullptr;

        std::unordered_map<std::string, Storage> meshStorages = {};
        std::string name = "";

        while (std::getline(file, line))
        {
            if (line.empty()) continue;

            if (line.at(0) == '#')
            {
                LOG_MESSAGE("Obj comment: {}", line); continue;
            }

            header = line.substr(0, line.find_first_of(' '));
            data = line.substr(line.find_first_of(' ') + 1);

            if (header == "mtllib")
            {
                std::string mtlfp(filepath);

#if GLEEC_WINDOWS
                for (char& c : mtlfp)
                {
                    if (c == '\\') c = '/';
                }
#endif

                mtl(mtlfp.substr(0, mtlfp.find_last_of('/') + 1) + data, geometry);
            }

            else if (header == "usemtl")
            {
                currentMesh->material = findMaterial(geometry, data);
            }

            else if (header == "v")
            {
                meshStorages.at(name).verts.push_back(read_triple(data));
            }

            else if (header == "vt")
            {
                meshStorages.at(name).uv.push_back(read_double(data));
            }

            else if (header == "vn")
            {
                meshStorages.at(name).norm.push_back(read_triple(data));
            }
            
            else if (header == "f")
            {
                addFace(data, meshStorages.at(name));
            }

            else if (header == "o")
            {
                currentMesh = &geometry.meshes.emplace_back(data);

                meshStorages[name = data] = {};
            }

            else
            {
                LOG_MESSAGE("Unknown OBJ header: {} with data: {}!",
                    header, data);
            }
        }

        for (auto& [_, storage] : meshStorages)
        {
            Mesh* mesh = findMesh(geometry, _);

#if GLEEC_RENDERER_MESH_PERSIST_VERTICES
            mesh->vertices = storage.meshVertices;
#else
            mesh->verticesSize = storage.meshVertices.size();
#endif

#if GLEEC_RENDERER_MESH_PERSIST_INDICES
            mesh->indices = storage.meshIndices;
#else
            mesh->indicesSize = storage.meshIndices.size();
#endif

            mesh->vertexBuffer = BufferManager::createVertexBuffer(
                storage.meshVertices);

            mesh->indexBuffer = BufferManager::createIndexBuffer(
                storage.meshIndices);
        }

        LOG_MESSAGE("Finished parsing obj file: {}!", filepath);

        LOG_MESSAGE("TODO: after doing geometry stuff need to do multithreading");

        return geometry;
    }

    void mtl(std::string_view filepath, Geometry& geometry)
    {
        std::fstream file(filepath.data());

        if (!file.is_open())
        {
            LOG_WARNING("Failed to parse mtl file: {}", filepath); return;
        }

        std::string line = "";
        std::string header = "";
        std::string data = "";
        std::string name = "";

        Material* currentMaterial = nullptr;
        std::unordered_map<std::string, ColorMaterial> colorMaterials = {};
        std::unordered_map<std::string, TextureMaterial> textureMaterials = {};

        while (std::getline(file, line))
        {
            if (line.empty()) continue;

            if (line.at(0) == '#')
            {
                LOG_MESSAGE("MTL comment: {}", line); continue;
            }

            header = line.substr(0, line.find_first_of(' '));
            data = line.substr(line.find_first_of(' ') + 1);

            if (header == "newmtl")
            {
                // by default create a color material,
                // but if map_Kd is found it will destroy it
                // and create a texture material instead
                name = data;

                colorMaterials[name] = {};
                colorMaterials[name].name = name;

                currentMaterial = &colorMaterials[name];
            }

            else if (header == "d")
            {
                currentMaterial->d = read_single(data);
            }

            else if (header == "Ka")
            {
                currentMaterial->ambient = read_triple(data);
            }

            else if (header == "Kd")
            {
                currentMaterial->diffuse = read_triple(data);
            }

            else if (header == "Ks")
            {
                currentMaterial->specular = read_triple(data);
            }

            else if (header == "Ns")
            {
                currentMaterial->shininess = read_single(data);
            }

            // texture map
            else if (header == "map_Kd")
            {
                // transfer the current color material
                // into a texture material
                TextureMaterial& temp = textureMaterials[name];
                temp.name = currentMaterial->name;

                temp.ambient = currentMaterial->ambient;
                temp.diffuse = currentMaterial->diffuse;
                temp.specular = currentMaterial->specular;
                temp.d = currentMaterial->d;

                temp.texture = TextureManager::findTexture(data);

                colorMaterials.erase(name);

                currentMaterial = &textureMaterials[name];
            }
            
            else
            {
                LOG_MESSAGE("Unknown MTL header: {} with data: {}!",
                    header, data);
            }
        }

#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        if (!colorMaterials.empty())
        {
            geometry.colorDescriptorBuffer =
                Internal::Graphics::vk::createDescriptorBuffer(
                    GPUManager::activeGPU.device.physicalDevice,
                    GPUManager::activeGPU.device,
                    GPUManager::activeGPU.allocator,
                    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0,
                    ShaderManager::getShaders("cl").descriptorSetLayouts[
                        GeometryManager::colorBuffer]);
        }

        for (auto& [_, material] : colorMaterials)
        {
            material.colorBuffer = BufferManager::createUniformBuffer(
                sizeof(math::vec4));

            /* material.offset = geometry.colorDescriptorBuffer.descriptors *
                geometry.colorDescriptorBuffer.descriptorSize; */

            material.shaderClass =
                std::hash<std::string_view>{}("cl");

            material.offset = Internal::Graphics::vk::getUniformBufferDescriptor(
                GPUManager::activeGPU.device.physicalDevice,
                GPUManager::activeGPU.device,
                GPUManager::activeGPU.allocator,
                geometry.colorDescriptorBuffer, material.colorBuffer.buffer);

            geometry.colorMaterials.push_back(std::move(material));
        }

        if (!textureMaterials.empty())
        {
            geometry.textureDescriptorBuffer =
                Internal::Graphics::vk::createDescriptorBuffer(
                    GPUManager::activeGPU.device.physicalDevice,
                    GPUManager::activeGPU.device,
                    GPUManager::activeGPU.allocator,
                    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0,
                    ShaderManager::getShaders("uv").descriptorSetLayouts[
                        GeometryManager::textureBuffer]);
        }

        for (auto& [_, material] : textureMaterials)
        {
            material.imageView = Internal::Graphics::vk::createColorImageView2D(
                GPUManager::activeGPU.device,
                material.texture.image, material.texture.image.format);

            material.sampler = Internal::Graphics::vk::createSampler(
                GPUManager::activeGPU.device);

            /* material.offset = geometry.textureDescriptorBuffer.descriptors *
                geometry.textureDescriptorBuffer.descriptorSize; */

            material.shaderClass =
                std::hash<std::string_view>{}("uv");

            material.offset = Internal::Graphics::vk::getCombinedImageSamplerDescriptor(
                GPUManager::activeGPU.device.physicalDevice,
                GPUManager::activeGPU.device,
                GPUManager::activeGPU.allocator,
                geometry.textureDescriptorBuffer,
                material.sampler, material.imageView);

            geometry.textureMaterials.push_back(std::move(material));
        }
#endif

        LOG_MESSAGE("Finished parsing mtl file: {}!", filepath);
    }
}
