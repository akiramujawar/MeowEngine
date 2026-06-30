//
// Created by Akira Mujawar on 08/09/22.
//

#include "Mesh.hpp"

#include <utility>

using MeowEngine::Mesh;

struct Mesh::Internal {
    std::vector<MeowEngine::Vertex> Vertices;
    std::vector<uint32_t> Indices;

    Internal() {}
};

MeowEngine::Mesh::Mesh()
    : InternalPointer(MeowEngine::make_internal_ptr<Internal>()) {
}

void Mesh::SetData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
    InternalPointer->Vertices = std::move(vertices);
    InternalPointer->Indices = std::move(indices);
}

const std::vector<MeowEngine::Vertex> &MeowEngine::Mesh::GetVertices() const {
    return InternalPointer->Vertices;
}

const std::vector<uint32_t> & MeowEngine::Mesh::GetIndices() const {
    return InternalPointer->Indices;
}

