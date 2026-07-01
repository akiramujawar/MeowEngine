//
// Created by Akira Mujawar on 08/09/22.
//

#include "MeshAsset.hpp"

#include <utility>

namespace MeowEngine::Asset {
    void MeshAsset::SetData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        Vertices = vertices;
        Indices = indices;
    }
}

// using MeowEngine::Asset::Mesh;
//
// struct Mesh::Internal {
//     std::vector<MeowEngine::Vertex> Vertices;
//     std::vector<uint32_t> Indices;
//
//     Internal() {}
// };
//
// Mesh::Mesh()
//     : InternalPointer(MeowEngine::make_internal_ptr<Internal>()) {
// }

// void Mesh::SetData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
//     InternalPointer->Vertices = std::move(vertices);
//     InternalPointer->Indices = std::move(indices);
// }
//
// const std::vector<MeowEngine::Vertex> &Mesh::GetVertices() const {
//     return InternalPointer->Vertices;
// }
//
// const std::vector<uint32_t> & Mesh::GetIndices() const {
//     return InternalPointer->Indices;
// }

