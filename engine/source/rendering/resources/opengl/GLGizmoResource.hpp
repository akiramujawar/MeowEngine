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
        int GetNumIndices() const { return IndexCount; }

    private:
        uint32_t VertexArrayObject;
        uint32_t VertexBufferObject;
        uint32_t ElementBufferObject;

        int IndexCount;
    };
}


#endif //MEOWENGINE_GLGIZMORESOURCE_HPP