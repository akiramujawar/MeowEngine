//
// Created by Akira Mujawar on 23/06/24.
//

#ifndef MEOWENGINE_GL_MESH_PIPELINE_HPP
#define MEOWENGINE_GL_MESH_PIPELINE_HPP


#include "GL_API.hpp"

#include "IRenderPipeline.hpp"

namespace MeowEngine::Rendering {
    struct MeshDrawData;

    class GLMeshPipeline : public IRenderPipeline {
    public:
        GLMeshPipeline();
        ~GLMeshPipeline() override = default;

        void Draw(const RenderContext& context, const MeshDrawData& data);

    private:
        bool IsInitialized = false;

        uint32_t UniformLocationMVP = - 1;
        uint32_t AttributeLocationVertexPosition = -1;
        uint32_t AttributeLocationTextureCoord = -1;
        int32_t Stride;
        int32_t OffsetPosition;
        int32_t OffsetTextureCoord;
    };
}


#endif //MEOWENGINE_GL_MESH_PIPELINE_HPP
