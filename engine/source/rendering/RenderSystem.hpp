//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_RENDERSYSTEM_HPP
#define MEOWENGINE_RENDERSYSTEM_HPP

#include <RenderGraph.hpp>
#include <GLWorldViewFrameBuffer.hpp>

#include <RuntimeRenderPipeline.hpp>
#include <EditorRenderPipeline.hpp>

#include <Public/Threading/Forward.hpp>

namespace MeowEngine::Graphics {
    class GraphicsDevice;
}

namespace MeowEngine::Rendering {
    class RenderSystem {
    public:
        RenderSystem(Graphics::GraphicsDevice& device);
        ~RenderSystem();

        void Schedule(Threading::Scheduler& scheduler, Graphics::GraphicsDevice& device);

    private:
        RenderGraph RenderGraph;

        /**
         * TODO: this is part of renderer (not graphics)
         * Draws our game view onto a ui panel (which is a framebuffer)
         */
        Graphics::GLWorldViewFrameBuffer WorldViewFrameBuffer;

        Runtime::RenderPipeline RuntimeRenderPipeline;
        Editor::RenderPipeline EditorRenderPipeline;
    };
}


#endif //MEOWENGINE_RENDERSYSTEM_HPP