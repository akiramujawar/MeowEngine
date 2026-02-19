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
            const OpenGLAssetManager& assetManager,
            const entity::TransformHandleComponent* renderComponent,
            const entity::Transform3DComponent* transform3DComponent,
            const PerspectiveCamera* camera
        ) const;

    private:
        void CreateHandle(std::vector<float>& vertices, std::vector<uint32_t>& indices);
        void AddAxisLines(std::vector<float>& pVertices,
                          std::vector<uint32_t>& pIndices,
                          const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                          int pAxis);
        void AddScaleCubes(std::vector<float>& pVertices,
                           std::vector<uint32_t>& pIndices,
                           const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                           int pAxis,
                           glm::vec3 pDirection);
        void AddArrowHeads(std::vector<float>& pVertices,
                           std::vector<uint32_t>& pIndices,
                           const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                           int pAxis,
                           glm::vec3 pDirection);
        void AddRotationRings(std::vector<uint32_t>& pIndices,
                              const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
                              int pAxis);

    private:
        const GLuint ShaderProgramID;

        GLuint VertexArrayObject;
        GLuint VertexBufferObject;
        GLuint ElementBufferObject;

        int IndexCount;
    };
}


#endif //MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP
