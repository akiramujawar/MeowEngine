//
// Created by Akira Mujawar on 01/07/26.
//

#include "GLGizmoResource.hpp"

#include "GL_API.hpp"
#include "MeowService.hpp"
#include "AssetManager.hpp"
#include "GizmoAsset.hpp"

namespace MeowEngine::Rendering {
    GLGizmoResource::GLGizmoResource(Asset::AssetHandle handle) {
        auto* asset = MeowService().AssetManager.GetAsset<Asset::GizmoAsset>(handle);

        IndexCount = asset->GetIndices().size();

        glGenVertexArrays(1, &VertexArrayObject);
        glGenBuffers(1, &VertexBufferObject);
        glGenBuffers(1, &ElementBufferObject);

        glBindVertexArray(VertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER,
                     asset->GetVertices().size() * sizeof(float),
                     asset->GetVertices().data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     asset->GetIndices().size() * sizeof(uint32_t),
                     asset->GetIndices().data(),
                     GL_STATIC_DRAW);

        GLsizei stride = 5 * sizeof(float);

        // positions of generated mesh vertices (location = 0)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              stride, (void *) 0);

        // axis (location = 1)
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE,
                              stride, (void *) (3 * sizeof(float)));

        // handle types (location = 2)
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE,
                              stride, (void *) (4 * sizeof(float)));

        glBindVertexArray(0);
    }

    GLGizmoResource::~GLGizmoResource() {
        glDeleteVertexArrays(1, &VertexArrayObject);
        glDeleteBuffers(1, &VertexArrayObject);
    }
}
