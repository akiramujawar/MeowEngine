//
// Created by Akira Mujawar on 12/09/22.
//

#ifndef MEOWENGINE_GLMESHRESOURCE_HPP
#define MEOWENGINE_GLMESHRESOURCE_HPP

// #include "GL_API.hpp"
// #include "mesh.hpp"
// #include "internal_ptr.hpp"

#include <AssetHandle.hpp>

namespace MeowEngine::Rendering {
    struct GLMeshResource {
        // GLMeshResource(const MeowEngine::Mesh& mesh);
        GLMeshResource(Asset::AssetHandle asset) {}

        // const GLuint & GetVertexArrayId() const;
        // const GLuint& GetVertexBufferId() const;
        // const GLuint& GetIndexBufferId() const;
        //
        // const uint32_t& GetNumIndices() const;

    // private:
        // struct Internal;
        // MeowEngine::internal_ptr<Internal> InternalPointer;
    };
} // namespace MeowEngine


#endif //MEOWENGINE_GLMESHRESOURCE_HPP
