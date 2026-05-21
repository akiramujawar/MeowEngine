//
// Created by Akira Mujawar on 22/06/24.
//

#ifndef MEOWENGINE_OPENGL_GRID_PIPELINE_HPP
#define MEOWENGINE_OPENGL_GRID_PIPELINE_HPP

#include "GLM_API.hpp"
#include "GL_API.hpp"

#include "IRenderPipeline.hpp"
#include "render_component_base.hpp"
#include "transform3d_component.hpp"
#include "perspective_camera.hpp"

using namespace std;
using namespace glm;

namespace MeowEngine {
    class OpenGLAssetManager;
}

namespace MeowEngine::pipeline {
    struct OpenGLGridPipeline : public Rendering::IRenderPipeline {
        OpenGLGridPipeline(const GLuint& shaderProgramID);
        ~OpenGLGridPipeline() override;

    public:
        void Render(
            const MeowEngine::OpenGLAssetManager& assetManager,
            const MeowEngine::entity::RenderComponentBase* renderComponent,
            const MeowEngine::PerspectiveCamera* camera
        ) const;

    private:
        const GLuint ShaderProgramID;
        unsigned int VertexArrayID;
    };
}

#endif //MEOWENGINE_OPENGL_GRID_PIPELINE_HPP
