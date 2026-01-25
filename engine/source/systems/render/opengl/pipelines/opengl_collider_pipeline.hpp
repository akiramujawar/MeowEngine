//
// Created by Akira Mujawar on 04/02/25.
//

#ifndef MEOWENGINE_OPENGL_COLLIDER_PIPELINE_HPP
#define MEOWENGINE_OPENGL_COLLIDER_PIPELINE_HPP

#include <opengl_box_collider.hpp>
#include <opengl_sphere_collider.hpp>
#include "graphics_wrapper.hpp"

#include "opengl_pipeline_base.hpp"
#include "perspective_camera.hpp"
#include "entt_wrapper.hpp"

namespace MeowEngine {

    struct OpenGLColliderPipeline : public MeowEngine::pipeline::OpenGLPipelineBase {
        OpenGLColliderPipeline(const GLuint& inShaderProgramID);
        ~OpenGLColliderPipeline() override;

    public:
        void Render(MeowEngine::PerspectiveCamera* cameraObject, entt::registry& registry);

    private:
        const GLuint ShaderProgramID;
        OpenGLBoxCollider BoxCollider;
        OpenGLSphereCollider SphereCollider;

        unsigned int VAO; // vertex array object (the sequence of VB0)
        unsigned int VBO; // vertex buffer object (positions / normals / uvs / colours)
        unsigned int EBO; // element buffer object (index list for drawing triangles)
        unsigned int instanceVBO; // optimization to draw same type mesh -- instance rendering
    };

} // MeowEngine

#endif //MEOWENGINE_OPENGL_COLLIDER_PIPELINE_HPP
