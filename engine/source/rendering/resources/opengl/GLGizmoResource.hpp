//
// Created by Akira Mujawar on 01/07/26.
//

#ifndef MEOWENGINE_GLGIZMORESOURCE_HPP
#define MEOWENGINE_GLGIZMORESOURCE_HPP

#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct GLGizmoResource {
        GLGizmoResource(Asset::AssetHandle handle);
        ~GLGizmoResource();

        uint32_t GetVertexArrayObject() const { return VertexArrayObject; }
        uint32_t GetNumIndices() const { return IndicesCount; }

    private:
        uint32_t VertexArrayObject;
        uint32_t VertexBufferObject;
        uint32_t ElementBufferObject;

        uint32_t IndicesCount;
    };
}


#endif //MEOWENGINE_GLGIZMORESOURCE_HPP