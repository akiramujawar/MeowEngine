//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERER_HPP
#define MEOWENGINE_RENDERER_HPP

#include <RenderGraph.hpp>
#include <GLWorldViewFrameBuffer.hpp>

#include <RuntimeRenderPipeline.hpp>
#include <EditorRenderPipeline.hpp>

#include <Public/Threading/Forward.hpp>

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Rendering {
    /**
     * Handles the various render pipelines, passes, graphs
     */
    class Renderer {
    public:
        Renderer(Graphics::GraphicsDevice& device);
        ~Renderer();

        void Schedule(Threading::Scheduler& scheduler, Graphics::GraphicsDevice& device);

    private:
        RenderGraph RenderGraph;

        /**
         * Draws our game view onto a ui panel (which is a framebuffer)
         */
        Graphics::GLWorldViewFrameBuffer WorldViewFrameBuffer;

        Runtime::RenderPipeline RuntimeRenderPipeline;
        Editor::RenderPipeline EditorRenderPipeline;
    };
}


#endif //MEOWENGINE_RENDERER_HPP