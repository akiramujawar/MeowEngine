//
// Created by Akira Mujawar on 22/06/24.
//

#ifndef MEOWENGINE_OPENGL_GRID_PIPELINE_HPP
#define MEOWENGINE_OPENGL_GRID_PIPELINE_HPP

#include "IRenderPipeline.hpp"


namespace MeowEngine::Rendering {
    struct GridDrawData;

    class OpenGLGridPipeline : public IRenderPipeline {
    public:
        OpenGLGridPipeline();
        ~OpenGLGridPipeline() override;

        void Draw(const RenderContext& context, GridDrawData& data) const;

    private:
        unsigned int VertexArrayID;
    };
}

#endif //MEOWENGINE_OPENGL_GRID_PIPELINE_HPP
