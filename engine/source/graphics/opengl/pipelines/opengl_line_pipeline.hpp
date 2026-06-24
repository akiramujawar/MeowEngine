//
// Created by Akira Mujawar on 22/06/24.
//

#ifndef MEOWENGINE_OPENGL_LINE_PIPELINE_HPP
#define MEOWENGINE_OPENGL_LINE_PIPELINE_HPP

#include "GLM_API.hpp"
#include "GL_API.hpp"

#include "IRenderPipeline.hpp"
#include "line_render_component.hpp"
#include "transform3d_component.hpp"
#include "perspective_camera.hpp"

using namespace std;
using namespace glm;

namespace MeowEngine {
    class OpenGLAssetManager;
}

namespace MeowEngine::pipeline {
    struct OpenGLLinePipeline : public Rendering::IRenderPipeline {
        OpenGLLinePipeline(const GLuint& shaderProgramID);
        ~OpenGLLinePipeline() override;

    public:
        void Render(
            const MeowEngine::OpenGLAssetManager& assetManager,
            const MeowEngine::Runtime::LineRenderComponent* lineRenderComponent,
            const MeowEngine::Runtime::Transform3DComponent* transform3DComponent,
            const MeowEngine::PerspectiveCamera* camera
        ) const;

    private:
        const GLuint ShaderProgramID;
        unsigned int VertexBufferID, VertexArrayID;
    };
}

#endif //MEOWENGINE_OPENGL_LINE_PIPELINE_HPP
