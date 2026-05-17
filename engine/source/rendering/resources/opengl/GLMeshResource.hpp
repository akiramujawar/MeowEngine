//
// Created by Akira Mujawar on 12/09/22.
//

#ifndef MEOWENGINE_GLMESHRESOURCE_HPP
#define MEOWENGINE_GLMESHRESOURCE_HPP

#include "GL_API.hpp"
#include "mesh.hpp"
#include "internal_ptr.hpp"

namespace MeowEngine {
    struct GLMeshResource {
        explicit GLMeshResource(const MeowEngine::Mesh& mesh);

        const GLuint & GetVertexArrayId() const;
        const GLuint& GetVertexBufferId() const;
        const GLuint& GetIndexBufferId() const;

        const uint32_t& GetNumIndices() const;

    private:
        struct Internal;
        MeowEngine::internal_ptr<Internal> InternalPointer;
    };
} // namespace MeowEngine


#endif //MEOWENGINE_GLMESHRESOURCE_HPP
