//
// Created by Akira Mujawar on 18/02/26.
//

#ifndef MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP
#define MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP

#include "GLM_API.hpp"

#include "IRenderPipeline.hpp"
#include "perspective_camera.hpp"

namespace MeowEngine::Rendering {
    struct TransformGizmoDrawData;

    /**
     * TODO: remove glm
     */
    class GLTransformGizmoPipeline : public IRenderPipeline {
    public:
        GLTransformGizmoPipeline();
        ~GLTransformGizmoPipeline() override;

        void Draw(const RenderContext& context, const TransformGizmoDrawData& data) const;

    // private:
    //     void CreateHandle(std::vector<float>& vertices, std::vector<uint32_t>& indices);
    //     void AddAxisLines(std::vector<float>& pVertices,
    //                       std::vector<uint32_t>& pIndices,
    //                       const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
    //                       int pAxis);
    //     void AddScaleCubes(std::vector<float>& pVertices,
    //                        std::vector<uint32_t>& pIndices,
    //                        const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
    //                        int pAxis,
    //                        glm::vec3 pDirection);
    //     void AddArrowHeads(std::vector<float>& pVertices,
    //                        std::vector<uint32_t>& pIndices,
    //                        const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
    //                        int pAxis,
    //                        glm::vec3 pDirection);
    //     void AddRotationRings(std::vector<uint32_t>& pIndices,
    //                           const std::function<uint32_t(glm::vec3, int, int)>& pAddVertex,
    //                           int pAxis);

    // private:
        // uint32_t VertexArrayObject;
        // uint32_t VertexBufferObject;
        // uint32_t ElementBufferObject;
        //
        // int IndexCount;
    };
}


#endif //MEOWENGINE_OPENGL_TRANSFORM_HANDLE_PIPELINE_HPP
