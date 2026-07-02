//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_GIZMOASSET_HPP
#define MEOWENGINE_GIZMOASSET_HPP

#include <vector>

#include "IAsset.hpp"

namespace MeowEngine::Asset {
    class GizmoAsset : public IAsset {
    public:
        [[nodiscard]] const std::vector<float>& GetVertices() const { return Vertices; }
        [[nodiscard]] const std::vector<uint32_t>& GetIndices() const  { return Indices;}

    protected:
        std::vector<float> Vertices;
        std::vector<uint32_t> Indices;
    };
}
#endif //MEOWENGINE_GIZMOASSET_HPP