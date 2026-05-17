//
// Created by Akira Mujawar on 13/05/26.
//

#ifndef MEOWENGINE_WORLDRENDERER_HPP
#define MEOWENGINE_WORLDRENDERER_HPP

#include <RenderGraph.hpp>
#include <GLWorldViewFrameBuffer.hpp>

#include <RuntimeWorldBuilder.hpp>
#include <EditorWorldBuilder.hpp>

#include <Public/Threading/Forward.hpp>

namespace MeowEngine::Rendering {
    struct RendererContext;

    /**
     * Handles the various render pipelines, passes, graphs
     */
    class WorldRenderer {
    public:
        WorldRenderer();
        ~WorldRenderer();

        void Init(RendererContext& context);
        void Schedule(Threading::Scheduler& scheduler);

    private:
        RenderGraph RenderGraph;

        /**
         * Draws our game view onto a ui panel (which is a framebuffer)
         */
        Graphics::GLWorldViewFrameBuffer WorldViewFrameBuffer;

        Runtime::RuntimeWorldBuilder RuntimeBuilder;
        Editor::EditorWorldBuilder EditorBuilder;
    };
}


#endif //MEOWENGINE_WORLDRENDERER_HPP