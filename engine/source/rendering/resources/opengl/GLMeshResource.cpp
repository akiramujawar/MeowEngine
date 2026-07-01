//
// Created by Akira Mujawar on 12/09/22.
//

#include "GLMeshResource.hpp"

// #include "GLM_API.hpp"
#include "GL_API.hpp"
#include "MeowService.hpp"
#include "AssetManager.hpp"
#include "MeshAsset.hpp"

namespace {
    using MeowEngine::Asset::MeshAsset;

    // Refer: https://registry.khronos.org/OpenGL-Refpages/es1.1/xhtml/glBindBuffer.xml for buffer types
    GLuint CreateVertexArrayID() {
        GLuint id;
        glGenVertexArrays(1, &id);

        return id;
    }

    GLuint CreateVertexBuffer(const MeshAsset& mesh) {
        std::vector<float> bufferData;

        for(const auto& vertex: mesh.GetVertices()) {
            bufferData.push_back(vertex.Position.x);
            bufferData.push_back(vertex.Position.y);
            bufferData.push_back(vertex.Position.z);

            bufferData.push_back(vertex.TextureCoord.x);
            bufferData.push_back(vertex.TextureCoord.y);
        }

        // Total Buffer data = pos + texturecoord (uv) = 3 + 2 = 5
        // 5 * float size = 20 bytes
        GLuint bufferId;
        glGenBuffers(1, &bufferId); // create empty buffer
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(
            GL_ARRAY_BUFFER,
            bufferData.size() * sizeof(float),
            bufferData.data(),
            GL_STATIC_DRAW
         );

        return bufferId;
    }

    GLuint CreateIndexBuffer(const MeshAsset& mesh) {
        GLuint bufferId;

        glGenBuffers(1, &bufferId); // create empty buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndices().size() * sizeof(uint32_t), mesh.GetIndices().data(), GL_STATIC_DRAW);

        return bufferId;
    }
} // namespace

// struct GLMeshResource::Internal {
//     const GLuint BufferIdVertices;
//      const GLuint BufferIdIndices;
//     const uint32_t IndicesCount;
//     const GLuint VertexArrayID;
//
//     explicit Internal(const MeowEngine::Mesh& mesh)
//         : BufferIdVertices(CreateVertexBuffer(mesh))
//         , BufferIdIndices(CreateIndexBuffer(mesh))
//         , IndicesCount(static_cast<uint32_t>(mesh.GetIndices().size()))
//         , VertexArrayID(CreateVertexArrayID())
//    {}
//
//     ~Internal() {
//         glDeleteVertexArrays(1, &VertexArrayID);
//         glDeleteBuffers(1, &BufferIdVertices);
//         glDeleteBuffers(1, &BufferIdIndices);
//     }
// };

namespace MeowEngine::Rendering {
    GLMeshResource::GLMeshResource(Asset::AssetHandle handle) {
        auto* asset = MeowService().AssetManager.GetAsset<Asset::MeshAsset>(handle);

        BufferIdVertices = CreateVertexBuffer(*asset);
        BufferIdIndices = CreateIndexBuffer(*asset);
        IndicesCount = static_cast<uint32_t>(asset->GetIndices().size());
        VertexArrayID = CreateVertexArrayID();
    }

    GLMeshResource::~GLMeshResource() {
        glDeleteVertexArrays(1, &VertexArrayID);
        glDeleteBuffers(1, &BufferIdVertices);
        glDeleteBuffers(1, &BufferIdIndices);
    }
}
// using MeowEngine::GLMeshResource;


//
// MeowEngine::GLMeshResource::GLMeshResource(const MeowEngine::Mesh &mesh)
// : InternalPointer(MeowEngine::make_internal_ptr<Internal>(mesh)) {}
//
// const GLuint &MeowEngine::GLMeshResource::GetVertexArrayId() const {
//     return InternalPointer->VertexArrayID;
// }
//
// const GLuint &MeowEngine::GLMeshResource::GetVertexBufferId() const {
//     return InternalPointer->BufferIdVertices;
// }
//
// const GLuint &MeowEngine::GLMeshResource::GetIndexBufferId() const {
//     return InternalPointer->BufferIdIndices;
// }
//
// const uint32_t &MeowEngine::GLMeshResource::GetNumIndices() const {
//     return InternalPointer->IndicesCount;
// }
