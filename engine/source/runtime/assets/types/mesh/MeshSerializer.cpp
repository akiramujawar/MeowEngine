//
// Created by Akira Mujawar on 01/07/26.
//

#include "MeshSerializer.hpp"

#include "tiny_obj_loader.h"
#include "Public/IO/Include.hpp"
#include "AssetSerializer.hpp"

namespace MeowEngine::Asset {
    bool MeshSerializer::Serialize(const Path& path, const std::string& data) {
        MeowEngine::Log("ShaderSerialization", "Serialize");

        // read existing header
        auto readSerializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);
        AssetHeader header;
        AssetSerializer::ReadHeader(readSerializer, header);

        AssetSerializer::CloseSerializer(readSerializer);

        // create temp
        auto tempPath = path;
        tempPath.ReplaceExtension("meowtemp");

        auto writeSerializer = AssetSerializer::OpenSerializer(tempPath, FileSystem::FileMode::WRITE);
        AssetSerializer::WriteHeader(writeSerializer, header);

        // write data
        writeSerializer.WriteString(data);

        // close & get back temp file
        AssetSerializer::CloseSerializer(writeSerializer);

        if (!FileSystem::FileSystem::Replace(path, tempPath)) {
            FileSystem::FileSystem::Remove(tempPath);

            return false;
        }

        return true;
    }

    bool MeshSerializer::Deserialize(const Path& path, MeshAsset& asset) {
        MeowEngine::Log("MeshSerializer", "Deserialize");

        auto serializer = AssetSerializer::OpenSerializer(path, FileSystem::FileMode::READ);

        // read header
        AssetHeader header;
        bool isValidAsset = AssetSerializer::ReadHeader(serializer, header);

        if (!isValidAsset) {
            return false;
        }

        // read data
        auto data = serializer.ReadString();

        // close serialization
        AssetSerializer::CloseSerializer(serializer);

        // decompress
        std::istringstream stream(data);
        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warning;
        std::string error;

        if(!tinyobj::LoadObj(
            &attributes,
            &shapes,
            &materials,
            &error,
            &stream
        )) {
            throw std::runtime_error("MeowEngine::assets::LoadObjFile: Error: "+error);
        }

        // convert to engine data
        std::vector<MeowEngine::Vertex> vertices;
        std::vector<uint32_t> indices;
        std::unordered_map<MeowEngine::Vertex, uint32_t> uniqueVertices;

        for(const auto& shape : shapes) {
            for(const auto& index : shape.mesh.indices) {
                // construct position vector for current mesh index
                glm::vec3 position {
                    attributes.vertices[3 * index.vertex_index + 0],
                    attributes.vertices[3 * index.vertex_index + 1],
                    attributes.vertices[3 * index.vertex_index + 2]
                };

                // construct (uv) texture coordinate for current mesh index
                glm::vec2 textureCoord {
                    attributes.texcoords[2 * index.texcoord_index + 0],
                    1.f - attributes.texcoords[2 * index.texcoord_index + 1]
                };

                // create vertex
                MeowEngine::Vertex vertex {
                    position,
                    textureCoord
                };

                // TODO: check this out.. what was that unique hashing with template and this
                // This will help deduplicate vertices - we maintain a hash map where a
                // vertex is used as a unique key with its value being which index can
                // be used to locate the vertex. The vertex is only added if it has not
                // been added before.
                if(uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }
        }

        // // NOTE: quick hack to fix coordinate system
        // // as we use perspectiveRH_NO & lookAtRH
        // for (size_t i = 0; i < indices.size(); i += 3) {
        //     std::swap(indices[i + 1], indices[i + 2]);
        // }

        // set asset data
        asset.SetData(vertices, indices);

        return true;
    }
}










