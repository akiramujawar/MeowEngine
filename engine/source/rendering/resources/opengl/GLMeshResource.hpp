//
// Created by Akira Mujawar on 12/09/22.
//

#ifndef MEOWENGINE_GLMESHRESOURCE_HPP
#define MEOWENGINE_GLMESHRESOURCE_HPP


#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct GLMeshResource {
        // GLMeshResource(const MeowEngine::Mesh& mesh);
        GLMeshResource(Asset::AssetHandle handle);
        ~GLMeshResource();

        [[nodiscard]] const uint32_t& GetVertexBufferId() const { return BufferIdVertices; };
        [[nodiscard]] const uint32_t& GetIndexBufferId() const { return BufferIdIndices;};
        [[nodiscard]] const uint32_t& GetNumIndices() const { return IndicesCount; };
        [[nodiscard]] const uint32_t & GetVertexArrayId() const { return VertexArrayID; };

    private:
        uint32_t BufferIdVertices;
        uint32_t BufferIdIndices;
        uint32_t IndicesCount;
        uint32_t VertexArrayID;

        // struct Internal;
        // MeowEngine::internal_ptr<Internal> InternalPointer;
    };
} // namespace MeowEngine


#endif //MEOWENGINE_GLMESHRESOURCE_HPP
