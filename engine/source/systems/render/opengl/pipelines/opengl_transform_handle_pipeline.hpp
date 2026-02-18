//
// Created by Akira Mujawar on 18/02/26.
//

#ifndef MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP
#define MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP

#include "glm_wrapper.hpp"
#include "graphics_wrapper.hpp"

#include "opengl_pipeline_base.hpp"
#include "transform_handle_component.hpp"

#include "transform3d_component.hpp"
#include "perspective_camera.hpp"

using namespace glm;

namespace MeowEngine::pipeline {
    struct OpenGLTransformHandlePipeline : public MeowEngine::pipeline::OpenGLPipelineBase {
        OpenGLTransformHandlePipeline(const GLuint& pShaderProgramID);
        ~OpenGLTransformHandlePipeline() override;

    public:
        void Render(
            const MeowEngine::OpenGLAssetManager& assetManager,
            const MeowEngine::entity::TransformHandleComponent* renderComponent,
            const MeowEngine::entity::Transform3DComponent* transform3DComponent,
            const MeowEngine::PerspectiveCamera* camera
        ) const;

    private:
        const GLuint ShaderProgramID;
        unsigned int VertexArrayObject;
    };
}


#endif //MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP
