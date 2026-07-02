//
// Created by Akira Mujawar on 08/09/22.
//

#ifndef MEOWENGINE_MESH_HPP
#define MEOWENGINE_MESH_HPP

#include <vector>

#include "IAsset.hpp"
// #include "internal_ptr.hpp"
#include "Vertex.hpp"

namespace MeowEngine::Asset  {
    struct MeshAsset : IAsset {
        MeshAsset() {}

        void SetData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

        [[nodiscard]] const std::vector<Vertex>& GetVertices() const { return Vertices; }
        [[nodiscard]] const std::vector<uint32_t>& GetIndices() const  { return Indices;}

    protected:
        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indices;
    //     struct Internal;
    //     MeowEngine::internal_ptr<Internal> InternalPointer;
    };
} // namespace MeowEngine


#endif //MEOWENGINE_MESH_HPP
